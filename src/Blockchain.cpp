#include "Blockchain.h"
#include "BlockFactory.h"

namespace blockchain {
Blockchain::Blockchain(Block genesisBlock_)
    : chain_({std::move(genesisBlock_)}) {}

Block Blockchain::getLatestBlock() const { return chain_[chain_.size() - 1]; }

Block Blockchain::addBlock(std::string data) {
  auto &lastBlock = chain_.back();
  std::time_t result = std::time(nullptr);
  auto newBlock = BlockFactory::create(lastBlock.getIndex() + 1, data, lastBlock.getDigest());
  chain_.emplace_back(newBlock);
  return newBlock;
}
} // namespace blockchain
