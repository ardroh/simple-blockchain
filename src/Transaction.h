#pragma once
#include <string>

namespace blockchain {
class Transaction {
public:
  Transaction(std::string fromAddress, std::string toAddress, double amount, double reward);
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
};
} // namespace blockchain
