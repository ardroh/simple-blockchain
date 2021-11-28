#include "Transaction.h"
#include "DigestCalculator.h"
#include "RSAMessageSigner.h"
#include <sstream>

namespace blockchain {
Transaction::Transaction(std::string fromAddress, std::string toAddress,
                         double amount, double reward)
    : fromAddress_(std::move(fromAddress)), toAddress_(std::move(toAddress)),
      amount_(std::move(amount)), reward_(reward) {}

bool Transaction::sign(const std::string &key, const std::string &keyPassword) {
  if (signature_.has_value()) {
    return false; // already signed
  }

  auto transDigest = DigestCalculator::calculate(this->getString());
  auto signature =
      RSAMessageSinger().Sign(transDigest.getString(), key, keyPassword);
  if (!signature.has_value()) {
    return false; // failed to sign
  }
  signature_ = signature.value();
  return true;
}

bool Transaction::verify() const {
  if (!signature_.has_value()) {
    return false; // not signed
  }
  auto digest = DigestCalculator::calculate(this->getString());
  return RSAMessageSinger().Verify(digest.getString(), fromAddress_,
                                   signature_.value());
}

std::string Transaction::getFromAddress() const { return fromAddress_; };
std::string Transaction::getToAddress() const { return toAddress_; };
double Transaction::getAmount() const { return amount_; };
double Transaction::getReward() const { return reward_; };

std::string Transaction::getString() const {
  std::stringstream ss;
  ss << "transaction=" << fromAddress_ << kStrDelim << toAddress_ << kStrDelim
     << amount_ << kStrDelim << reward_ << kStrDelim;
  return ss.str();
};

} // namespace blockchain
