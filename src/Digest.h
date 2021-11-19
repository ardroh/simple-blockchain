#pragma once
#include <cstdio>
#include <vector>
#include <string>

namespace blockchain {
class Digest {
public:
  Digest() = default;
  Digest(std::vector<unsigned char> digest);
  Digest(const std::string & strDigest);
  std::string getString() const;
  std::vector<unsigned char> getArray() const;
  bool compare(const Digest & other) const;

private:
  std::vector<unsigned char> digest_;
};
} // namespace blockchain
