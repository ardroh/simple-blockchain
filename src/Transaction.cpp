#include "Transaction.h"

namespace blockchain {
Transaction::Transaction(std::string fromAddress, std::string toAddress,
                         double amount, double reward)
    : fromAddress_(std::move(fromAddress)), toAddress_(std::move(toAddress)),
      amount_(std::move(amount)), reward_(reward) {}

std::string Transaction::getFromAddress() const { return fromAddress_; };
std::string Transaction::getToAddress() const { return toAddress_; };
double Transaction::getAmount() const { return amount_; };
double Transaction::getReward() const { return reward_; };

std::string Transaction::getString() const {
    return fromAddress_ + toAddress_ + std::to_string(amount_) + std::to_string(reward_);
};

} // namespace blockchain
