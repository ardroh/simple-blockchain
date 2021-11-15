#pragma once
#include <string>

namespace blockchain {
struct RSAKeyPair {
  std::string publicKey;
  std::string privateKey;
};
} // namespace blockchain
