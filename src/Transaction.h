#pragma once
#include <string>

namespace blockchain {
class Transaction {
public:
  Transaction(std::string fromAddress, std::string toAddress, double amount);
  std::string getFromAddress() const;
  std::string getToAddress() const;
  double getAmount() const;
  std::string getString() const;

private:
  std::string fromAddress_;
  std::string toAddress_;
  double amount_;
};
} // namespace blockchain
