#include "RSAMessageSigner.h"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

namespace blockchain {
std::optional<Digest> RSAMessageSinger::Sign(const std::string &message,
                                             const std::string &privateKey) {
  RSA *rsa = nullptr;
  auto cPrivateKey = privateKey.c_str();
  BIO *keybio = BIO_new_mem_buf((void *)cPrivateKey, -1);
  if (keybio == nullptr) {
    return {};
  } 

  EVP_MD_CTX *rsaSignCtx = EVP_MD_CTX_new();
  EVP_PKEY *priKey = EVP_PKEY_new();
  PEM_read_bio_PrivateKey(keybio, &priKey, 0,  0);
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
} // namespace blockchain
