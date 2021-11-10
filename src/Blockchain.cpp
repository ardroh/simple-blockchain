#include "Blockchain.h"
#include "BlockFactory.h"
#include "DigestCalculator.h"

namespace blockchain {
Blockchain::Blockchain(Block genesisBlock_)
    : chain_({std::move(genesisBlock_)}) {}

Block Blockchain::getLatestBlock() const { return chain_[chain_.size() - 1]; }

Block Blockchain::addBlock(std::string data) {
  auto &lastBlock = chain_.back();
  std::time_t result = std::time(nullptr);
  auto newBlock = BlockFactory::create(lastBlock.getIndex() + 1, data,
                                       lastBlock.getDigest());
  chain_.emplace_back(newBlock);
  return newBlock;
}

bool Blockchain::verifyChain() const {
  for (size_t i = 1; i < chain_.size(); i++) {
    auto currentBlock = this->chain_[i];
    auto previousBlock = this->chain_[i - 1];

    if (!currentBlock.getDigest().compare(DigestCalculator::calculate(
            currentBlock.getIndex(),
            currentBlock.getPreviousDigest().getString(),
            currentBlock.getTimestamp(), currentBlock.getData()))) {
      return false;
    }

    if (!currentBlock.getPreviousDigest().compare(previousBlock.getDigest())) {
      return false;
    }
    return true;
  }
}
} // namespace blockchain
