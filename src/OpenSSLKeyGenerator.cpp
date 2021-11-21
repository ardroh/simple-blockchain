#include "OpenSSLKeyGenerator.h"
#include <array>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <vector>

namespace blockchain {
IKeyGenerator::KeyPair
OpenSSLKeyGenerator::generateKeys(const std::string &password) {
  if (password.empty()) {
    return {};
  }

  auto primes = 3u;
  auto keyLength = 2048u;
  // Generate keys
  EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_from_name(NULL, "RSA", NULL);
  EVP_PKEY_keygen_init(pctx);
  std::array<OSSL_PARAM, 3> params;
  params[0] = OSSL_PARAM_construct_uint("bits", &keyLength);
  params[1] = OSSL_PARAM_construct_uint("primes", &primes);
  params[2] = OSSL_PARAM_construct_end();
  EVP_PKEY_CTX_set_params(pctx, params.data());
  EVP_PKEY *pkey = NULL;
  EVP_PKEY_generate(pctx, &pkey);
  EVP_PKEY_CTX_free(pctx);

  // Write keys to BIO's
  auto bioPublic = BIO_new(BIO_s_mem());
  PEM_write_bio_PUBKEY(bioPublic, pkey);
  auto bioPrivate = BIO_new(BIO_s_mem());
  PEM_write_bio_PrivateKey(
      bioPrivate, pkey, EVP_des_ede3_cbc(),
      reinterpret_cast<const unsigned char *>(password.c_str()),
      password.length(), 0, NULL);

  // Stringify the keys
  std::vector<unsigned char> public_key, private_key;
  auto pub_len = BIO_pending(bioPublic);
  public_key.resize(pub_len + 1);
  BIO_read(bioPublic, public_key.data(), pub_len);
  BIO_free(bioPublic);
  auto pri_len = BIO_pending(bioPrivate);
  private_key.resize(pri_len + 1);
  BIO_read(bioPrivate, private_key.data(), pri_len);
  BIO_free(bioPrivate);

  return {
      std::string(std::begin(public_key), std::end(public_key)),
      std::string(std::begin(private_key), std::end(private_key)),
  };
}
} // namespace blockchain
