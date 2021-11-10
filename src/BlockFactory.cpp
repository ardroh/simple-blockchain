#include "BlockFactory.h"
#include <openssl/evp.h>

namespace blockchain {
std::vector<unsigned char> calculateDigest(int index, const std::string & previousDigest, std::time_t timestamp, const std::string & data) {
  EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
  EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
  auto message = std::to_string(index) + previousDigest +
                 std::to_string(timestamp) + data;
  EVP_DigestUpdate(mdctx, message.c_str(), message.length());
  auto rawDigest =
      static_cast<unsigned char *>(OPENSSL_malloc(EVP_MD_size(EVP_sha256())));
  unsigned digestLen;
  EVP_DigestFinal_ex(mdctx, rawDigest, &digestLen);
  EVP_MD_CTX_destroy(mdctx);
  std::vector<unsigned char> digest(rawDigest, rawDigest + digestLen);
  OPENSSL_free(rawDigest);
  return digest;
}

Block BlockFactory::create(int index, const std::string & data, const Digest & previousDigest) {
    std::time_t result = std::time(nullptr);
    auto digest = calculateDigest(index, previousDigest.getString(), result, data);
    return Block(index, result, data, previousDigest, digest);
}
} // namespace blockchain
