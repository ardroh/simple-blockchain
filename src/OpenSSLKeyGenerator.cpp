#include "OpenSSLKeyGenerator.h"
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <vector>

namespace blockchain {
RSAKeyPair OpenSSLKeyGenerator::generateKeys() {
  int ret = 0;
  RSA *r = nullptr;
  BIGNUM *bne = nullptr;
  BIO *bp_public = nullptr, *bp_private = nullptr;

  int bits = 2048;
  unsigned long e = RSA_F4;

  // 1. generate rsa key
  bne = BN_new();
  ret = BN_set_word(bne, e);
  if (ret != 1) {
    return {};
  }

  r = RSA_new();
  ret = RSA_generate_key_ex(r, bits, bne, NULL);
  if (ret != 1) {
    return {};
  }

  bp_public = BIO_new(BIO_s_mem());
  ret = PEM_write_bio_RSAPublicKey(bp_public, r);
  if (ret != 1) {
    return {};
  }

  bp_private = BIO_new(BIO_s_mem());
  ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);

  size_t pri_len; // Length of private key
  size_t pub_len; // Length of public key

  pri_len = BIO_pending(bp_private);
  pub_len = BIO_pending(bp_public);
  std::vector<char> pri_key, pub_key;
  pri_key.resize(pri_len + 1);
  pub_key.resize(pub_len + 1);

  BIO_read(bp_private, pri_key.data(), pri_len);
  BIO_read(bp_public, pub_key.data(), pub_len);

  return {std::string(std::begin(pub_key), std::end(pub_key)),
          std::string(std::begin(pri_key), std::end(pri_key))};
}
} // namespace blockchain
