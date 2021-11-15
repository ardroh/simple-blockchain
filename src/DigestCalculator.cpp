#include "DigestCalculator.h"
#include <openssl/evp.h>
#include <sstream>

namespace blockchain {
Digest DigestCalculator::calculate(const std::string & message) {
  EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
  EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
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
