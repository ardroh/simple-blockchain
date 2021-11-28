#pragma once
#include "Digest.h"
#include <optional>
#include <string>

namespace blockchain {
class Transaction {
private:
  static const char kStrDelim = ';';

public:
  Transaction(std::string fromAddress, std::string toAddress, double amount,
              double reward);

  bool sign(const std::string &key, const std::string &keyPassword);
  bool verify() const;
  std::string getFromAddress() const;
  std::string getToAddress() const;
  double getAmount() const;
  double getReward() const;
  std::string getString() const;

private:
  std::string fromAddress_;
  std::string toAddress_;
  double amount_;
  double reward_;
  std::optional<Digest> signature_;
};
} // namespace blockchain
