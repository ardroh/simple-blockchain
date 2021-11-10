#include "Block.h"
#include <openssl/evp.h>

namespace blockchain {
Block::Block(int index, std::time_t timestamp, std::string data,
             Digest previousDigest, Digest currentDigest)
    : index_(index), timestamp_(timestamp), data_(data),
      previousDigest_(previousDigest), digest_(std::move(currentDigest)) {}

int Block::getIndex() const { return index_; }
std::time_t Block::getTimestamp() const { return timestamp_; }
std::string Block::getData() const { return data_; }
Digest Block::getDigest() const { return digest_; }
Digest Block::getPreviousDigest() const { return previousDigest_; }

} // namespace blockchain