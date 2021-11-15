#pragma once
#include "IMessageSigner.h"

namespace blockchain {
class RSAMessageSinger : public IMessagesSigner {
public:
  ~RSAMessageSinger() override = default;
  std::optional<Digest> Sign(const std::string &message,
                             const std::string &privateKey) override;
};
} // namespace blockchain
