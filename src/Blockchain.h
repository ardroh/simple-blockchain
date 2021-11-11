#pragma once
#include "Block.h"
#include <future>
#include <optional>

namespace blockchain {
class Blockchain {
public:
  explicit Blockchain(Block genesisBlock_, unsigned difficulty);

  Block getLatestBlock() const;
  std::future<std::optional<Block>> addNewBlockAsync(const std::string &data, std::future<bool> terminationRequest);
  bool verifyChain() const;

private:
  std::vector<Block> chain_;
  unsigned difficulty_ = 2;
  std::string expectedDigestPrefix_;
};
} // namespace blockchain
