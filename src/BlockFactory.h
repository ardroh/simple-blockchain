#pragma once
#include "Digest.h"
#include "Block.h"
#include <string>

namespace blockchain {
class BlockFactory {
public:
  static Block create(int index, const std::string & data, const Digest & previousDigest);
};
} // namespace blockchain
