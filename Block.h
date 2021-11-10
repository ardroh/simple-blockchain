#pragma once
#include "Digest.h"
#include <array>
#include <string>

namespace blockchain {
class Block {
public:
  Block(int index, unsigned long timestamp, std::string data,
        Digest previousDigest);
  ~Block() = default;

  Digest GetDigest() const;

private:
  void calculateHash();

private:
  int index_;
  unsigned long timestamp_;
  std::string data_;
  Digest digest_;
  Digest previousDigest_;
};
}; // namespace blockchain