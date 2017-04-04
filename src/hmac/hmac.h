#ifndef __HMAC_HMAC
#define __HMAC_HMAC
#include <stdint.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/x509.h>

#include "sha3/digest.h"

typedef uint8_t Hmac_Byte;
typedef void (*MD_FUNC)(SHA_Byte *buff, size_t buff_len, SHA_Byte *digest);

#define HMAC_SHA3_DIGEST_LEN 64

void _hmac(
    MD_FUNC   hash,             // Hash function
    size_t    hash_blocksize,   // Hash function Block Size
    size_t    hash_digestsize,  // Hash digest size
    uint8_t   *buff,            // Message
    size_t    buff_len,         // Message Length
    uint8_t   *key,             // Key
    size_t    key_len,          // Key Length
    uint8_t   *digest           // HMAC digest
);

void hmac_sha512(uint8_t *buff, int buff_len, uint8_t *key, int key_len, void *digest);
void hmac_sha3(uint8_t *buff, int buff_len, uint8_t *key, int key_len, void *digest);

#endif