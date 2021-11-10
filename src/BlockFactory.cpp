#include "BlockFactory.h"
#include "DigestCalculator.h"

namespace blockchain {
Block BlockFactory::create(int index, const std::string & data, const Digest & previousDigest) {
    std::time_t timestamp = std::time(nullptr);
    auto digest = DigestCalculator::calculate(index, previousDigest.getString(), timestamp, data);
    return Block(index, timestamp, data, previousDigest, digest);
}
} // namespace blockchain
