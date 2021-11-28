#include "Blockchain.h"
#include "DigestCalculator.h"
#include <cassert>
#include <chrono>
#include <numeric>

namespace blockchain {
Blockchain::Blockchain(Block genesisBlock_, unsigned difficulty)
    : chain_({std::move(genesisBlock_)}), difficulty_(difficulty) {
  expectedDigestPrefix_ = std::string(difficulty_, '0');
}

Block Blockchain::getLatestBlock() const { return chain_[chain_.size() - 1]; }

void Blockchain::minePendingTransactions(const std::string &rewardAddress) {
  std::unique_lock<std::mutex> lock(pendingTransactionsMutex_);
  auto &lastBlock = chain_.back();
  std::time_t timestamp = std::time(nullptr);
  auto nounce = 0ull;
  std::optional<Block> optBlock;
  auto startT = std::chrono::high_resolution_clock::now();
  while (true) {
    auto tempBlock =
        Block(timestamp, pendingTransactions_, lastBlock.getDigest(), nounce);
    if (tempBlock.getDigest().getString().compare(
            0, expectedDigestPrefix_.size(), expectedDigestPrefix_) == 0) {
      optBlock = tempBlock;
      break;
    }

    nounce++;
  }
  auto endT = std::chrono::high_resolution_clock::now();
  printf(
      "Mining took: %lld ms\n",
      static_cast<long long int>(
          std::chrono::duration_cast<std::chrono::milliseconds>(endT - startT)
              .count()));
  if (!optBlock.has_value()) {
    assert(false);
    return;
  }

  auto newBlock = optBlock.value();

  chain_.emplace_back(newBlock);
  auto rewardSum = std::accumulate(std::begin(pendingTransactions_),
                                   std::end(pendingTransactions_), 0.0,
                                   [](double sum, const Transaction &trans) {
                                     return sum + trans.getReward();
                                   });
  pendingTransactions_.push_back({{}, rewardAddress, rewardSum, 0.0});
}

bool Blockchain::verifyChain() const {
  for (size_t i = 1; i < chain_.size(); i++) {
    auto currentBlock = this->chain_[i];
    auto previousBlock = this->chain_[i - 1];

    if (!currentBlock.getDigest().compare(
            DigestCalculator::calculate(currentBlock.getString())) != 0) {
      return false;
    }

    if (!currentBlock.getPreviousDigest().compare(previousBlock.getDigest())) {
      return false;
    }
  }
  return true;
}

bool Blockchain::addNewTransaction(Transaction transaction) {
  if (!transaction.verify()) {
    return false; // incorrect signature or not signed
  }

  auto srcAmount = getAmountOfAddress(transaction.getFromAddress());
  if (srcAmount < transaction.getAmount() + transaction.getReward()) {
    return false;
  }
  std::unique_lock<std::mutex> lock(pendingTransactionsMutex_);
  pendingTransactions_.emplace_back(std::move(transaction));
  return true;
}

double Blockchain::getAmountOfAddress(const std::string &address) const {
  double balance = 0.0;
  for (const auto &block : chain_) {
    for (const auto &trans : block.getTransactions()) {
      if (trans.getFromAddress().compare(address) == 0) {
        balance -= trans.getAmount();
      } else if (trans.getToAddress().compare(address) == 0) {
        balance += trans.getAmount() - trans.getReward();
      }
    }
  }
  return balance;
};
} // namespace blockchain
