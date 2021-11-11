#pragma once
#include "Digest.h"

namespace blockchain
{
    class DigestCalculator {
    public:
        static Digest calculate(int index, const std::string & previousDigest, std::time_t timestamp, const std::string & data, unsigned long long nounce);
    };
} // namespace blockchain
