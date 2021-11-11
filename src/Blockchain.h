#pragma once
#include "Block.h"
#include "Transaction.h"
#include <future>
#include <mutex>
#include <optional>
#include <vector>

namespace blockchain {
class Blockchain {
public:
  explicit Blockchain(Block genesisBlock_, unsigned difficulty);

  Block getLatestBlock() const;
  void minePendingTransactions(const std::string &rewardAddress);
  bool verifyChain() const;
  void addNewTransaction(Transaction transaction);
  double getAmountOfAddress(const std::string & address) const;

private:
  std::vector<Block> chain_;
  unsigned difficulty_ = 2;
  std::string expectedDigestPrefix_;
  std::mutex pendingTransactionsMutex_;
  std::vector<Transaction> pendingTransactions_;
};
} // namespace blockchain
