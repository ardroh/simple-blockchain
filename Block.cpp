#include "Block.h"
#include <openssl/evp.h>

namespace blockchain {
Block::Block(int index, unsigned long timestamp, std::string data,
             Digest previousDigest)
    : index_(index), timestamp_(timestamp), data_(data),
      previousDigest_(previousDigest) {
  printf("before calc");
  calculateHash();
}

Digest Block::GetDigest() const { return digest_; }

void Block::calculateHash() {
  EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
  EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
  auto message = std::to_string(index_) + previousDigest_.GetString() +
                 std::to_string(timestamp_) + data_;
  EVP_DigestUpdate(mdctx, message.c_str(), message.length());
  auto rawDigest =
      static_cast<unsigned char *>(OPENSSL_malloc(EVP_MD_size(EVP_sha256())));
  unsigned digestLen;
  EVP_DigestFinal_ex(mdctx, rawDigest, &digestLen);
  EVP_MD_CTX_destroy(mdctx);
  std::vector<unsigned char> digest(rawDigest, rawDigest + digestLen);
  digest_ = {digest};
  OPENSSL_free(rawDigest);
}
} // namespace blockchain