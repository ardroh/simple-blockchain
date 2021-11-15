#pragma once
#include <tuple>
#include "RSAKeyPair.h"

namespace blockchain {
class IKeyGenerator {
public:
  virtual ~IKeyGenerator() = default;
  virtual RSAKeyPair generateKeys() = 0;
};
} // namespace blockchain
