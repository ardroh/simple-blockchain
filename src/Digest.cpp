#include "Digest.h"

namespace blockchain {
Digest::Digest(std::vector<unsigned char> digest)
    : digest_(std::move(digest)) {}

std::string Digest::GetString() const {
  auto digestSize = digest_.size();
  char outputBuffer[digestSize * 2 + 1];
  for (auto i = 0; i < digestSize; i++) {
    sprintf(outputBuffer + (i * 2), "%02x", digest_[i]);
  }
  outputBuffer[digestSize * 2] = 0;
  return outputBuffer;
}
} // namespace blockchain
