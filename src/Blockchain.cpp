#include "Blockchain.h"
#include "DigestCalculator.h"
#include <chrono>

namespace blockchain {
Blockchain::Blockchain(Block genesisBlock_, unsigned difficulty)
    : chain_({std::move(genesisBlock_)}), difficulty_(difficulty) {
  expectedDigestPrefix_ = std::string(difficulty_, '0');
}

Block Blockchain::getLatestBlock() const { return chain_[chain_.size() - 1]; }

void Blockchain::minePendingTransactions(const std::string & rewardAddress) {
  std::unique_lock<std::mutex> lock(pendingTransactionsMutex_);
  auto &lastBlock = chain_.back();
  std::time_t timestamp = std::time(nullptr);
  auto nounce = 0ull;
  std::optional<Digest> optDigest;
  auto startT = std::chrono::high_resolution_clock::now();
  while (true) {
    auto digest =
        DigestCalculator::calculate(lastBlock.getDigest().getString(),
                                    timestamp, pendingTransactions_, nounce);
    if (digest.getString().compare(0, expectedDigestPrefix_.size(),
                                   expectedDigestPrefix_) == 0) {
      optDigest = digest;
      break;
    }

    nounce++;
  }
  auto endT = std::chrono::high_resolution_clock::now();
  printf("Took: %lld ms\n",
         std::chrono::duration_cast<std::chrono::milliseconds>(endT - startT)
             .count());
  if (!optDigest.has_value()) {
    assert(false);
    return;
  }

  auto digest = optDigest.value();


  auto newBlock = Block(timestamp, pendingTransactions_,
                        lastBlock.getDigest(), digest, nounce);
  chain_.emplace_back(newBlock);
  pendingTransactions_.push_back({{}, rewardAddress, 100.0});
}

bool Blockchain::verifyChain() const {
  for (size_t i = 1; i < chain_.size(); i++) {
    auto currentBlock = this->chain_[i];
    auto previousBlock = this->chain_[i - 1];

    if (!currentBlock.getDigest().compare(DigestCalculator::calculate(
            currentBlock.getPreviousDigest().getString(),
            currentBlock.getTimestamp(), currentBlock.getTransactions(),
            currentBlock.getNounce()))) {
      return false;
    }

    if (!currentBlock.getPreviousDigest().compare(previousBlock.getDigest())) {
      return false;
    }
  }
  return true;
}

void Blockchain::addNewTransaction(Transaction transaction) {
  std::unique_lock<std::mutex> lock(pendingTransactionsMutex_);
  pendingTransactions_.emplace_back(std::move(transaction));
}

double Blockchain::getAmountOfAddress(const std::string &address) const {
  double balance = 0.0;
  for (const auto &block : chain_) {
    for (const auto &trans : block.getTransactions()) {
      if (trans.getFromAddress().compare(address) == 0) {
        balance -= trans.getAmount();
      } else if (trans.getToAddress().compare(address) == 0) {
        balance += trans.getAmount();
      }
    }
  }
  return balance;
};
} // namespace blockchain
