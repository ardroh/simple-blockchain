#pragma once
#include "Digest.h"
#include "Transaction.h"
#include <array>
#include <ctime>
#include <string>
#include <vector>

namespace blockchain {
class Block {
public:
  Block(std::time_t timestamp, std::vector<Transaction> transactions,
        Digest previousDigest, Digest currentDigest, unsigned long long nounce);
  ~Block() = default;

  std::time_t getTimestamp() const;
  std::vector<Transaction> getTransactions() const;
  Digest getDigest() const;
  Digest getPreviousDigest() const;
  unsigned long long getNounce() const;
  void setNounce(unsigned long long newNounce);
  std::string getString() const;

private:
  std::time_t timestamp_;
  std::vector<Transaction> transactions_;
  Digest digest_;
  Digest previousDigest_;
  unsigned long long nounce_;
};
}; // namespace blockchain