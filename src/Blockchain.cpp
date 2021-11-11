#include "Blockchain.h"
#include "DigestCalculator.h"
#include <chrono>

namespace blockchain {
Blockchain::Blockchain(Block genesisBlock_, unsigned difficulty)
    : chain_({std::move(genesisBlock_)}), difficulty_(difficulty) {
  expectedDigestPrefix_ = std::string(difficulty_, '0');
}

Block Blockchain::getLatestBlock() const { return chain_[chain_.size() - 1]; }

std::future<std::optional<Block>>
Blockchain::addNewBlockAsync(const std::string &data,
                             std::future<bool> terminationRequest) {
  auto promise = std::promise<std::optional<Block>>();
  auto future = promise.get_future();
  auto worker = [&](std::promise<std::optional<Block>> barrier,
                    std::future<bool> terminationRequest) {
    auto &lastBlock = chain_.back();
    std::time_t timestamp = std::time(nullptr);
    auto nounce = 0ull;
    const auto newIndex = lastBlock.getIndex() + 1;
    std::optional<Digest> optDigest;
    auto startT = std::chrono::high_resolution_clock::now();
    while (terminationRequest.wait_for(std::chrono::nanoseconds(1)) !=
           std::future_status::ready) {
      auto digest = DigestCalculator::calculate(
          newIndex, lastBlock.getDigest().getString(), timestamp, data, nounce);
      if (digest.getString().compare(0, expectedDigestPrefix_.size(),
                                     expectedDigestPrefix_) == 0) {
        optDigest = digest;
        break;
      }

      nounce++;
    }
    auto endT = std::chrono::high_resolution_clock::now();
    printf("Took: %lld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(endT-startT).count());
    if (!optDigest.has_value()) {
      barrier.set_value({});
      return;
    }

    auto digest = optDigest.value();

    auto newBlock =
        Block(newIndex, timestamp, data, lastBlock.getDigest(), digest, nounce);
    chain_.emplace_back(newBlock);
    barrier.set_value(newBlock);
  };
  auto t =
      std::thread(worker, std::move(promise), std::move(terminationRequest));
  t.detach();
  return future;
}

bool Blockchain::verifyChain() const {
  for (size_t i = 1; i < chain_.size(); i++) {
    auto currentBlock = this->chain_[i];
    auto previousBlock = this->chain_[i - 1];

    if (!currentBlock.getDigest().compare(DigestCalculator::calculate(
            currentBlock.getIndex(),
            currentBlock.getPreviousDigest().getString(),
            currentBlock.getTimestamp(), currentBlock.getData(),
            currentBlock.getNounce()))) {
      return false;
    }

    if (!currentBlock.getPreviousDigest().compare(previousBlock.getDigest())) {
      return false;
    }
  }
  return true;
}
} // namespace blockchain
