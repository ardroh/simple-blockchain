#include "BlockchainFactory.h"
#include "Block.h"
#include "BlockFactory.h"

namespace blockchain {
std::unique_ptr<Blockchain> BlockchainFactory::create() {
  Block genesisBlock = BlockFactory::create(0, "Genesis block", {});
  return std::make_unique<Blockchain>(genesisBlock);
}
} // namespace blockchain
