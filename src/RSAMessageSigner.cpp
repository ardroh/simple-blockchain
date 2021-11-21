#include "RSAMessageSigner.h"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

namespace blockchain {
std::optional<Digest> RSAMessageSinger::Sign(const std::string &message,
                                             const std::string &privateKey,
                                             const std::string &keyPassword) {
  auto cPrivateKey = privateKey.c_str();
  BIO *keybio = BIO_new_mem_buf((void *)cPrivateKey, -1);
  if (keybio == nullptr) {
    return {};
  }

  EVP_MD_CTX *rsaSignCtx = EVP_MD_CTX_new();
  EVP_PKEY *priKey = EVP_PKEY_new();
  auto callback = [](char *buf, int size, int rwflag, void *u) {
    auto keyPassword = static_cast<std::string*>(u);
    if (keyPassword == nullptr)
    {
      return 0;
    }
    memcpy(buf, keyPassword->c_str(), keyPassword->length());
    return static_cast<int>(keyPassword->length());
  };
  auto passwordCopy = keyPassword;
  PEM_read_bio_PrivateKey(keybio, &priKey, callback, &passwordCopy);
  if (EVP_DigestSignInit(rsaSignCtx, NULL, EVP_sha256(), NULL, priKey) <= 0) {
    return {};
  }
  if (EVP_DigestSignUpdate(rsaSignCtx, message.c_str(), message.length()) <=
      0) {
    return {};
  }
  size_t signatureLength = 0u;
  if (EVP_DigestSignFinal(rsaSignCtx, NULL, &signatureLength) <= 0) {
    return {};
  }
  std::vector<unsigned char> signature(signatureLength);
  if (EVP_DigestSignFinal(rsaSignCtx, signature.data(), &signatureLength) <=
      0) {
    return {};
  }
  EVP_MD_CTX_free(rsaSignCtx);
  return {signature};
}

bool RSAMessageSinger::Verify(const std::string &message,
                              const std::string &publicKey,
                              const Digest &signature) {
  auto cKey = publicKey.c_str();
  auto keyBio = BIO_new_mem_buf((void *)cKey, -1);
  if (keyBio == nullptr) {
    return false;
  }
  EVP_PKEY *pKey = EVP_PKEY_new();
  PEM_read_bio_PUBKEY(keyBio, &pKey, 0, 0);
  EVP_MD_CTX *rsaCtx = EVP_MD_CTX_new();
  if (EVP_DigestVerifyInit(rsaCtx, nullptr, EVP_sha256(), nullptr, pKey) <= 0) {
    return false;
  }
  if (EVP_DigestVerifyUpdate(rsaCtx, message.c_str(), message.length()) <= 0) {
    return false;
  }
  auto signatureData = signature.getArray();
  if (EVP_DigestVerifyFinal(rsaCtx, signatureData.data(),
                            signatureData.size()) <= 0) {
    return false;
  }
  return true;
}
} // namespace blockchain
