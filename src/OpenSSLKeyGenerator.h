#pragma once
#include "IKeyGenerator.h"

namespace blockchain
{
    class OpenSSLKeyGenerator: public IKeyGenerator {
    public:
        ~OpenSSLKeyGenerator() override = default;
        KeyPair generateKeys(const std::string & password) override;
    };
} // namespace blockchain
