#pragma once
#include "Digest.h"
#include <optional>
#include <string>
#include <vector>

namespace blockchain {
class IMessageSigner {
public:
  virtual ~IMessageSigner() = default;
  virtual std::optional<Digest> Sign(const std::string &message,
                                     const std::string &privateKey,
                                     const std::string &keyPassword) = 0;
  virtual bool Verify(const std::string &message, const std::string &publicKey,
                      const Digest &signature) = 0;
};
} // namespace blockchain