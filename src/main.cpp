#include "BlockchainFactory.h"
#include "OpenSSLKeyGenerator.h"
#include <ctime>
#include <iostream>

static unsigned const kDifficulty = 2;

int main(int argc, char *argv[]) {
  auto keyGenerator = blockchain::OpenSSLKeyGenerator();
  auto account1Pwd = "pwd1";
  auto account1Keys = keyGenerator.generateKeys(account1Pwd);
  auto account2Pwd = "pwd2";
  auto account2Keys = keyGenerator.generateKeys(account2Pwd);
  auto blockchain = blockchain::BlockchainFactory::create(kDifficulty);
  auto trans1 = blockchain::Transaction{account1Keys.publicKey,
                                        account2Keys.publicKey, 10, 1};
  auto isSigned = trans1.sign(account1Keys.privateKey, account1Pwd);
  if (!isSigned) {
    printf("Failed to sign first transaction.\n");
    return -1;
  }

  auto isAdded = blockchain->addNewTransaction(trans1);
  if (!isAdded) {
    printf("Failed to add 1st transaction.\n");
    return -1;
  }

  blockchain->minePendingTransactions(account1Keys.publicKey);
  std::cout << "address2 balance: "
            << blockchain->getAmountOfAddress(account2Keys.publicKey)
            << std::endl;
  std::cout << "address1 balance: "
            << blockchain->getAmountOfAddress(account1Keys.publicKey)
            << std::endl;
  blockchain->minePendingTransactions(account1Keys.publicKey);
  std::cout << "account1 balance: "
            << blockchain->getAmountOfAddress(account1Keys.publicKey)
            << std::endl;
  return 0;
}