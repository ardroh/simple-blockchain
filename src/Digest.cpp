#include "Digest.h"

namespace blockchain {
Digest::Digest(std::vector<unsigned char> digest)
    : digest_(std::move(digest)) {}

std::string Digest::getString() const {
  auto digestSize = digest_.size();
  char outputBuffer[digestSize * 2 + 1];
  for (auto i = 0; i < digestSize; i++) {
    sprintf(outputBuffer + (i * 2), "%02x", digest_[i]);
  }
  outputBuffer[digestSize * 2] = 0;
  return outputBuffer;
}

std::vector<unsigned char> Digest::getArray() const { return digest_; }

bool Digest::compare(const Digest &other) const {
  auto otherDigestArray = other.getArray();
  if (digest_.size() != otherDigestArray.size()) {
    return false;
  }

  for (size_t i = 0; i < digest_.size(); i++) {
    if (digest_[i] != otherDigestArray[i]) {
      return false;
    }
  }
  return true;
}
} // namespace blockchain
