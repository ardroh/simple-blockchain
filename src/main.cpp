#include "BlockchainFactory.h"
#include <iostream>
#include <ctime>

int main(int argc, char *argv[])
{
    auto blockchain = blockchain::BlockchainFactory::create();
    auto genesisBlock = blockchain->getLatestBlock();
    std::cout << "Genesis block digest: " << genesisBlock.getDigest().getString() << std::endl;
    for (size_t i = 0; i < 100; i++)
    {
        auto newBlock = blockchain->addBlock("transaction" + std::to_string(i));
        std::cout << "\t> " << newBlock.getPreviousDigest().getString() << " -> " << newBlock.getDigest().getString() << std::endl;
        std::cout << "\t\t> Is chain valid: " << blockchain->verifyChain() << std::endl;
    }
    return 0;
}