#pragma once
#include "IKeyGenerator.h"

namespace blockchain
{
    class OpenSSLKeyGenerator: public IKeyGenerator {
    public:
        ~OpenSSLKeyGenerator() override = default;
        RSAKeyPair generateKeys();
    };
} // namespace blockchain
