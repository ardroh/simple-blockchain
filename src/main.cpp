#include "BlockchainFactory.h"
#include <ctime>
#include <iostream>

static unsigned const kDifficulty = 2;

int main(int argc, char *argv[]) {
  auto blockchain = blockchain::BlockchainFactory::create(kDifficulty);
  blockchain->addNewTransaction({"address1", "address2", 10});
  blockchain->addNewTransaction({"address2", "address3", 10});
  blockchain->addNewTransaction({"address1", "address2", 10});
  blockchain->addNewTransaction({"address1", "address2", 10});
  blockchain->addNewTransaction({"address2", "address1", 10});
  blockchain->minePendingTransactions("abc");
  std::cout << "address2 balance: " << blockchain->getAmountOfAddress("address2") << std::endl;
  std::cout << "address1 balance: " << blockchain->getAmountOfAddress("address1") << std::endl;
  blockchain->minePendingTransactions("abc");
  std::cout << "abc balance: " << blockchain->getAmountOfAddress("abc") << std::endl;
  return 0;
}