#include "BlockchainFactory.h"
#include <ctime>
#include <iostream>

static unsigned const kDifficulty = 6;

int main(int argc, char *argv[]) {
  auto blockchain = blockchain::BlockchainFactory::create(kDifficulty);
  auto genesisBlock = blockchain->getLatestBlock();
  std::cout << "Genesis block digest: " << genesisBlock.getDigest().getString()
            << std::endl;
  for (size_t i = 0; i < 5; i++) {
    // auto newBlock = blockchain->addBlock("transaction" + std::to_string(i));
    std::cout << "calling new block.." << std::endl;
    auto addTerminationRequestPromise = std::promise<bool>();
    auto newBlockFuture = blockchain->addNewBlockAsync(
        "transaction" + std::to_string(i),
        std::move(addTerminationRequestPromise.get_future()));
    std::cout << "waiting.." << std::endl;
    auto result = newBlockFuture.wait_for(std::chrono::milliseconds(30000));
    if (result != std::future_status::ready) {
      std::cout << "too long. terminating";
      addTerminationRequestPromise.set_value(true);
      continue;
    }

    auto newBlock = newBlockFuture.get();
    if (!newBlock.has_value()) {
      std::cout << "no value :(" << std::endl;
      continue;
    }

    std::cout << "\t> " << newBlock.value().getPreviousDigest().getString()
              << " -> " << newBlock.value().getDigest().getString()
              << std::endl;
    std::cout << "\t\t> Is chain valid: " << blockchain->verifyChain()
              << std::endl;
  }
  return 0;
}