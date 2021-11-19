#include "Digest.h"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(DigestTest, ReturnsEqualityForSameDigests) {
  auto a = blockchain::Digest(std::vector<unsigned char>{0x1, 0x2, 0x3, 0x0});
  auto b = blockchain::Digest(std::vector<unsigned char>{0x1, 0x2, 0x3, 0x0});
  EXPECT_TRUE(a.compare(b));
}

// Demonstrate some basic assertions.
TEST(DigestTest, ReturnsNotEqualForSameDigests) {
  auto a = blockchain::Digest(std::vector<unsigned char>{0x1, 0x2, 0x3, 0x0});
  auto b = blockchain::Digest(std::vector<unsigned char>{0x1, 0x3, 0x3, 0x0});
  EXPECT_FALSE(a.compare(b));
}

TEST(DigestTest, GeneratesCorrectDigestString) {
    auto sut = blockchain::Digest(std::vector<unsigned char>{'a', 'b', 'c'});

    EXPECT_EQ(sut.getString(), "616263");
}

TEST(DigestTest, GeneratesCorrectDigestArray) {
    std::string testString("616263");
    auto sut = blockchain::Digest(testString);

    auto array = sut.getArray();

    EXPECT_EQ(array[0], 'a');
}