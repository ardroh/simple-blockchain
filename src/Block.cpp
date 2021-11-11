#include "Block.h"
#include <openssl/evp.h>

namespace blockchain {
Block::Block(int index, std::time_t timestamp, std::string data,
             Digest previousDigest, Digest currentDigest, unsigned long long nounce)
    : index_(index), timestamp_(timestamp), data_(data),
      previousDigest_(previousDigest), digest_(std::move(currentDigest)), nounce_(nounce) {}

int Block::getIndex() const { return index_; }
std::time_t Block::getTimestamp() const { return timestamp_; }
std::string Block::getData() const { return data_; }
Digest Block::getDigest() const { return digest_; }
Digest Block::getPreviousDigest() const { return previousDigest_; }

unsigned long long Block::getNounce() const { return nounce_; };
void Block::setNounce(unsigned long long newNounce) { nounce_ = newNounce; };

} // namespace blockchain