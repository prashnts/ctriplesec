#include "hmac.h"

void hmac_sha512(uint8_t *buff, int buff_len, uint8_t *key, int key_len, void *digest) {
  unsigned int result_len;
  uint8_t result[EVP_MAX_MD_SIZE];

  HMAC(EVP_sha512(),
       key, key_len,
       buff, buff_len,
       result, &result_len);
  memcpy(digest, result, result_len);
}

void _hmac(
    MD_FUNC   hash,
    size_t    hash_blocksize,
    size_t    hash_digestsize,
    uint8_t   *buff,
    size_t    buff_len,
    uint8_t   *key,
    size_t    key_len,
    uint8_t   *digest
) {
  const int blocksize = SHA3_512_BLOCKSIZE;
  uint8_t xkey[hash_blocksize];

  uint8_t outer_key_pad[hash_blocksize];
  uint8_t inner_key_pad[hash_blocksize];

  memset(xkey, 0x00, hash_blocksize);

  if (key_len > hash_blocksize) {
    hash(key, key_len, xkey);
  } else {
    memcpy(xkey, key, key_len);
  }

  for (int i=0; i < hash_blocksize; i++) {
    outer_key_pad[i] = 0x5c ^ xkey[i];
    inner_key_pad[i] = 0x36 ^ xkey[i];
  }

  uint8_t *inner_message = malloc(buff_len + hash_blocksize);
  uint8_t outer_message[hash_blocksize + hash_digestsize];
  uint8_t inner_hash[hash_digestsize];

  memcpy(inner_message, inner_key_pad, hash_blocksize);
  memcpy(inner_message + hash_blocksize, buff, buff_len);

  hash(inner_message, buff_len + hash_blocksize, inner_hash);

  memcpy(outer_message, outer_key_pad, hash_blocksize);
  memcpy(outer_message + hash_blocksize, inner_hash, hash_digestsize);

  hash(outer_message, hash_blocksize + hash_digestsize, digest);

  free(inner_message);
}


void hmac_sha3(uint8_t *buff, int buff_len, uint8_t *key, int key_len, void *digest) {
  _hmac(sha3_512, SHA3_512_BLOCKSIZE, SHA3_512_DIGESTSIZE, buff, buff_len, key, key_len, digest);
}