#pragma once
#include <cstdio>
#include <vector>
#include <string>

namespace blockchain {
class Digest {
public:
  Digest() = default;
  Digest(std::vector<unsigned char> digest);
  std::string getString() const;

private:
  std::vector<unsigned char> digest_;
};
} // namespace blockchain
