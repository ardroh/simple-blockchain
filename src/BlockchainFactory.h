#pragma once
#include "Blockchain.h"

namespace blockchain {
class BlockchainFactory {
public:
  static std::unique_ptr<Blockchain> create(unsigned difficulty);
};
} // namespace blockchain
