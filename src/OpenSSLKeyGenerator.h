#pragma once
#include "IKeyGenerator.h"

namespace blockchain
{
    class OpenSSLKeyGenerator: public IKeyGenerator {
    public:
        ~OpenSSLKeyGenerator() override = default;
        KeyPair generateKeys() override;
    };
} // namespace blockchain
