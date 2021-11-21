#pragma once
#include "IMessageSigner.h"

namespace blockchain {
class RSAMessageSinger : public IMessageSigner {
public:
  ~RSAMessageSinger() override = default;
  std::optional<Digest> Sign(const std::string &message,
                             const std::string &privateKey,
                             const std::string &keyPassword) override;
  bool Verify(const std::string &message, const std::string &publicKey,
              const Digest &signature) override;
};
} // namespace blockchain
