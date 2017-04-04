#include "digest.h"

void sha3_512(SHA_Byte *buffer, size_t buffer_len, SHA_Byte *digest) {
  sha3_ctx context;
  rhash_sha3_512_init(&context);
  rhash_sha3_update(&context, buffer, buffer_len);
  rhash_sha3_final(&context, digest);
}
