#include <gtest/gtest.h>
#include "OpenSSLKeyGenerator.h"

TEST(OpenSSLKeyGeneratorTests, CheckIfGeneratesAnyKeys) {
    constexpr auto pwd = "abc";
    auto sut = blockchain::OpenSSLKeyGenerator();

    auto keys = sut.generateKeys(pwd);

    ASSERT_FALSE(keys.publicKey.empty());
    ASSERT_FALSE(keys.privateKey.empty());
}

TEST(OpenSSLKeyGeneratorTests, CheckIfDoesntGenerateKeysWhenNoPassword) {
    constexpr auto pwd = "";
    auto sut = blockchain::OpenSSLKeyGenerator();

    auto keys = sut.generateKeys(pwd);

    ASSERT_TRUE(keys.publicKey.empty());
    ASSERT_TRUE(keys.privateKey.empty());
}