#pragma once
#include "Digest.h"
#include "Transaction.h"
#include <ctime>
#include <vector>

namespace blockchain {
class DigestCalculator {
public:
  static Digest calculate(const std::string &previousDigest,
                          std::time_t timestamp,
                          const std::vector<Transaction> &transactions,
                          unsigned long long nounce);
};
} // namespace blockchain
