#include "Block.h"
#include "DigestCalculator.h"
#include <sstream>

namespace blockchain {
Block::Block(std::time_t timestamp, std::vector<Transaction> transactions,
             Digest previousDigest, unsigned long long nounce)
    : timestamp_(timestamp), transactions_(transactions),
      previousDigest_(previousDigest), nounce_(nounce) {
  digest_ = DigestCalculator::calculate(getString());
}

std::time_t Block::getTimestamp() const { return timestamp_; }
std::vector<Transaction> Block::getTransactions() const {
  return transactions_;
};
Digest Block::getDigest() const { return digest_; }
Digest Block::getPreviousDigest() const { return previousDigest_; }

unsigned long long Block::getNounce() const { return nounce_; };
void Block::setNounce(unsigned long long newNounce) { nounce_ = newNounce; };

std::string Block::getString() const {
  std::stringstream ss;
  ss << "block=" << previousDigest_.getString() << kStrDelim << timestamp_
     << kStrDelim << nounce_ << kStrDelim;
  for (const auto &transaction : transactions_) {
    ss << transaction.getString();
  }
  ss << kStrDelim;

  return ss.str();
};
} // namespace blockchain