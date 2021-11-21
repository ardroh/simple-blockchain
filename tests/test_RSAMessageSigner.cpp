#include "OpenSSLKeyGenerator.h"
#include "RSAMessageSigner.h"
#include <gtest/gtest.h>

TEST(RSAMessageSignerTests, CheckIfCanSignAndVerifyTheMessage) {
  const std::string message = "abc";
  std::string keyPassword = "abc";
  auto keys = blockchain::OpenSSLKeyGenerator().generateKeys(keyPassword);
  auto sut = blockchain::RSAMessageSinger();

  auto signature = sut.Sign(message, keys.privateKey, keyPassword);
  ASSERT_TRUE(signature.has_value());
  ASSERT_TRUE(sut.Verify(message, keys.publicKey, signature.value()));
}

TEST(RSAMessageSignerTests, CheckIfFailsVerifyOnChangedPublicKey) {
  const std::string message = "abc";
  std::string keyPassword = "abc";
  auto keys = blockchain::OpenSSLKeyGenerator().generateKeys(keyPassword);
  auto sut = blockchain::RSAMessageSinger();
  auto keyBeginning = keys.publicKey.find("\n") + 1;
  std::string modification = "abcsdfasdsa";
  auto modifiedPubKey =
      keys.publicKey.substr(0, keyBeginning) + modification +
      keys.publicKey.substr(keyBeginning + modification.length());
  auto signature = sut.Sign(message, keys.privateKey, keyPassword);
  EXPECT_TRUE(signature.has_value());

  ASSERT_FALSE(sut.Verify(message, modifiedPubKey, signature.value()));
}



TEST(RSAMessageSignerTests, CheckIfFailsVerifyOnModifiedSignature) {
  const std::string message = "abc";
  std::string keyPassword = "abc";
  auto keys = blockchain::OpenSSLKeyGenerator().generateKeys(keyPassword);
  auto sut = blockchain::RSAMessageSinger();
  auto signature = sut.Sign(message, keys.privateKey, keyPassword);
  EXPECT_TRUE(signature.has_value());
  auto signatureData = signature.value().getArray();
  signatureData[0] += 1; 
  auto modifiedSignature = blockchain::Digest(signatureData);

  ASSERT_FALSE(sut.Verify(message, keys.publicKey, modifiedSignature));
}