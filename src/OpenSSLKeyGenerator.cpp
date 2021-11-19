#include "OpenSSLKeyGenerator.h"
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <vector>

namespace blockchain {
IKeyGenerator::KeyPair OpenSSLKeyGenerator::generateKeys() {
  unsigned int primes = 3;
  unsigned int bits = 1024;
  OSSL_PARAM params[3];
  EVP_PKEY *pkey = NULL;
  EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_from_name(NULL, "RSA", NULL);

  EVP_PKEY_keygen_init(pctx);

  params[0] = OSSL_PARAM_construct_uint("bits", &bits);
  params[1] = OSSL_PARAM_construct_uint("primes", &primes);
  params[2] = OSSL_PARAM_construct_end();
  EVP_PKEY_CTX_set_params(pctx, params);

  auto bp_public = BIO_new(BIO_s_mem());
  auto bp_private = BIO_new(BIO_s_mem());
  EVP_PKEY_generate(pctx, &pkey);
  EVP_PKEY_print_private(bp_private, pkey, 0, NULL);
  EVP_PKEY_print_public(bp_public, pkey, 0, NULL);
  EVP_PKEY_CTX_free(pctx);

  std::vector<unsigned char> public_key, private_key;
  auto pub_len = BIO_pending(bp_public);
  public_key.resize(pub_len + 1);
  BIO_read(bp_public, public_key.data(), pub_len);
  BIO_free(bp_public);
  auto pri_len = BIO_pending(bp_private);
  private_key.resize(pri_len + 1);
  BIO_read(bp_private, private_key.data(), pri_len);
  BIO_free(bp_private);

  return {
      std::string(std::begin(public_key), std::end(public_key)),
      std::string(std::begin(private_key), std::end(private_key)),
  };
}
} // namespace blockchain
