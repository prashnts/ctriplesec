#include "triplesec.h"


void triplesec_encrypt(uint8_t *pswd, size_t pswd_len, uint8_t *msg, size_t msg_len, uint8_t *cipher) {
  sodium_init();
  Twofish_initialise();

  uint8_t salt[TSEC_SALT_SIZE];
  uint8_t key[TSEC__SCRYPT_LEN];
  uint8_t iv_salsa20[TSEC__IV_SALSA20_LEN],
          iv_twofish[TSEC__IV_TWOFISH_LEN],
          iv_aes[TSEC__IV_AES_LEN];

  uint8_t key_salsa20[TSEC__KEY_SALSA20_LEN],
          key_twofish[TSEC__KEY_TWOFISH_LEN],
          key_aes[TSEC__KEY_AES_LEN],
          key_hmac_sha512[TSEC__KEY_HMAC_SHA512_LEN],
          key_hmac_sha3[TSEC__KEY_HMAC_SHA3_LEN];

  size_t len_salsa20 = msg_len,
         len_twofish = len_salsa20 + TSEC__IV_SALSA20_LEN,
         len_aes     = len_twofish + TSEC__IV_TWOFISH_LEN;

  uint8_t *pad_salsa20 = malloc(len_salsa20),
          *pad_twofish = malloc(len_twofish),
          *pad_aes     = malloc(len_aes);

  uint8_t *msg_twofish = malloc(len_twofish),
          *msg_aes     = malloc(len_aes);

  int scrypt_retval, offset = 0;

  randombytes_buf(salt, TSEC_SALT_SIZE);

  // Generate Initial Values
  randombytes_buf(iv_salsa20, TSEC__IV_SALSA20_LEN);
  randombytes_buf(iv_twofish, TSEC__IV_TWOFISH_LEN);
  randombytes_buf(iv_aes,     TSEC__IV_AES_LEN);

  scrypt_retval = libscrypt_scrypt(
    pswd, pswd_len,
    salt, TSEC_SALT_SIZE,
    TSEC__SCRYPT_N, TSEC__SCRYPT_r, TSEC__SCRYPT_p,
    key, TSEC__SCRYPT_LEN);

  if (scrypt_retval != 0) {
    // error!
  }

  // Split scrypt key into five keys
  memcpy(key_salsa20,     key + offset, TSEC__KEY_SALSA20_LEN);
  offset += TSEC__KEY_SALSA20_LEN;
  memcpy(key_twofish,     key + offset, TSEC__KEY_TWOFISH_LEN);
  offset += TSEC__KEY_TWOFISH_LEN;
  memcpy(key_aes,         key + offset, TSEC__KEY_AES_LEN);
  offset += TSEC__KEY_AES_LEN;
  memcpy(key_hmac_sha512, key + offset, TSEC__KEY_HMAC_SHA512_LEN);
  offset += TSEC__KEY_HMAC_SHA512_LEN;
  memcpy(key_hmac_sha3,   key + offset, TSEC__KEY_HMAC_SHA3_LEN);

  // XSalsa20
  crypto_stream_xor(pad_salsa20, msg, msg_len, iv_salsa20, key_salsa20);

  memcpy(msg_twofish, iv_salsa20, TSEC__IV_SALSA20_LEN);
  memcpy(msg_twofish + TSEC__IV_SALSA20_LEN, pad_salsa20, len_salsa20);

  // Twofish in CTR
  Twofish_key xkey;
  Twofish_prepare_key(key_twofish, 32, &xkey);
  Twofish_encrypt_ctr(&xkey, iv_twofish, msg_twofish, len_twofish, pad_twofish);

  memcpy(msg_aes, iv_twofish, TSEC__IV_TWOFISH_LEN);
  memcpy(msg_aes + TSEC__IV_TWOFISH_LEN, pad_twofish, len_twofish);

  // AES in CTR

  free(pad_salsa20);
  free(pad_twofish);
  free(pad_aes);
  free(msg_twofish);
  free(msg_aes);
}
