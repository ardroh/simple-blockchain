#pragma once
#include "Digest.h"
#include <array>
#include <string>

namespace blockchain {
class Block {
public:
  Block(int index, std::time_t timestamp, std::string data,
        Digest previousDigest, Digest currentDigest, unsigned long long nounce);
  ~Block() = default;

  int getIndex() const;
  std::time_t getTimestamp() const;
  std::string getData() const;
  Digest getDigest() const;
  Digest getPreviousDigest() const;
  unsigned long long getNounce() const;
  void setNounce(unsigned long long newNounce);

private:
  int index_;
  std::time_t timestamp_;
  std::string data_;
  Digest digest_;
  Digest previousDigest_;
  unsigned long long nounce_;
};
}; // namespace blockchain