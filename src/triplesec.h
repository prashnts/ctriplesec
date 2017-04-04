#ifndef __TRIPLESEC
#define __TRIPLESEC

#include <stdint.h>
#include <stdlib.h>

#include "sodium.h"
#include "scrypt/libscrypt.h"
#include "twofish/twofish.h"
#include "utils/io.h"

#define TSEC_SALT_SIZE  16

#define TSEC__SCRYPT_N   32768
#define TSEC__SCRYPT_r   8
#define TSEC__SCRYPT_p   1
#define TSEC__SCRYPT_LEN  192

#define TSEC__IV_SALSA20_LEN  192 / 8
#define TSEC__IV_TWOFISH_LEN  128 / 8
#define TSEC__IV_AES_LEN      128 / 8

#define TSEC__KEY_SALSA20_LEN 32
#define TSEC__KEY_TWOFISH_LEN 32
#define TSEC__KEY_AES_LEN     32
#define TSEC__KEY_HMAC_SHA512_LEN 48
#define TSEC__KEY_HMAC_SHA3_LEN   48

void triplesec_encrypt(
    uint8_t *pswd, size_t pswd_len,
    uint8_t *msg, size_t msg_len,
    uint8_t *cipher);

#endif
