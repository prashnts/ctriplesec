#ifndef __SHA3_DIGEST
#define __SHA3_DIGEST

#include <stdint.h>

#include "sha3.h"

#define SHA3_512_BLOCKSIZE 72
#define SHA3_512_DIGESTSIZE 64

typedef uint8_t SHA_Byte;

void sha3_512(SHA_Byte *buffer, size_t buffer_len, SHA_Byte *digest);

#endif