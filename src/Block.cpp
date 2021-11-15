#include "Block.h"
#include <sstream>

namespace blockchain {
Block::Block(std::time_t timestamp, std::vector<Transaction> transactions,
             Digest previousDigest, Digest currentDigest,
             unsigned long long nounce)
    : timestamp_(timestamp), transactions_(transactions),
      previousDigest_(previousDigest), digest_(std::move(currentDigest)),
      nounce_(nounce) {}

std::time_t Block::getTimestamp() const { return timestamp_; }
std::vector<Transaction> Block::getTransactions() const { return transactions_; };
Digest Block::getDigest() const { return digest_; }
Digest Block::getPreviousDigest() const { return previousDigest_; }

unsigned long long Block::getNounce() const { return nounce_; };
void Block::setNounce(unsigned long long newNounce) { nounce_ = newNounce; };

std::string Block::getString() const {
  auto dataBuilder = std::stringstream();
  for (const auto &transaction : transactions_) {
    dataBuilder << transaction.getString();
  }

  return previousDigest_.getString() + std::to_string(timestamp_) +
                 dataBuilder.str() + std::to_string(nounce_);
};

} // namespace blockchain