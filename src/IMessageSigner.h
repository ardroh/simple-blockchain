#pragma once
#include "Digest.h"
#include <optional>
#include <string>
#include <vector>

namespace blockchain {
class IMessagesSigner {
public:
  virtual ~IMessagesSigner() = default;
  virtual std::optional<Digest> Sign(const std::string &message,
                                     const std::string &privateKey) = 0;
};
} // namespace blockchain