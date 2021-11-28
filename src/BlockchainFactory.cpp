#include "BlockchainFactory.h"
#include "Block.h"

namespace blockchain {
std::unique_ptr<Blockchain> BlockchainFactory::create(unsigned difficulty) {
  Block genesisBlock = Block(0, {}, {}, 0ull);
  return std::make_unique<Blockchain>(genesisBlock, difficulty);
}
} // namespace blockchain
