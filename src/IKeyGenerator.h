#pragma once
#include "Digest.h"
#include "RSAKeyPair.h"
#include <tuple>

namespace blockchain {
class IKeyGenerator {
public:
  struct KeyPair {
    std::string publicKey;
    std::string privateKey;
  };
  virtual ~IKeyGenerator() = default;
  virtual KeyPair generateKeys(const std::string & password) = 0;
};
} // namespace blockchain
