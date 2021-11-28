#pragma once
#include "Digest.h"
#include "Transaction.h"
#include <ctime>
#include <vector>

namespace blockchain {
class DigestCalculator {
public:
  static Digest calculate(const std::string & message);
};
} // namespace blockchain
