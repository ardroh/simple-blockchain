#include "DigestCalculator.h"
#include <openssl/evp.h>
#include <sstream>

namespace blockchain {
Digest DigestCalculator::calculate(const std::string &previousDigest,
                                   std::time_t timestamp,
                                   const std::vector<Transaction> &transactions,
                                   unsigned long long nounce) {
  EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
  EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
  auto dataBuilder = std::stringstream();
  for (const auto &transaction : transactions) {
    dataBuilder << transaction.getString();
  }

  auto message = previousDigest + std::to_string(timestamp) +
                 dataBuilder.str() + std::to_string(nounce);
  EVP_DigestUpdate(mdctx, message.c_str(), message.length());
  auto rawDigest =
      static_cast<unsigned char *>(OPENSSL_malloc(EVP_MD_size(EVP_sha256())));
  unsigned digestLen;
  EVP_DigestFinal_ex(mdctx, rawDigest, &digestLen);
  EVP_MD_CTX_destroy(mdctx);
  std::vector<unsigned char> digest(rawDigest, rawDigest + digestLen);
  OPENSSL_free(rawDigest);
  return {digest};
}
} // namespace blockchain
