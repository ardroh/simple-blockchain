#include "Block.h"
#include <iostream>
#include <ctime>

int main(int argc, char *argv[])
{
    std::time_t result = std::time(nullptr);
    std::cout << ("beffore block") << std::endl;
    auto b = blockchain::Block(0, result, {}, {});
    std::cout << "Digest: " << b.GetDigest().GetString() << std::endl;
    return 0;
}