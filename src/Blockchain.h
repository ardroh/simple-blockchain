#pragma once
#include "Block.h"

namespace blockchain {
class Blockchain {
public:
  explicit Blockchain(Block genesisBlock_);

    Block getLatestBlock() const;
    Block addBlock(std::string data);
    bool verifyChain() const;
    
private:
  std::vector<Block> chain_;
};
} // namespace blockchain
