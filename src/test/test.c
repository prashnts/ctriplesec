#include <stdio.h>
#include <string.h>

#include "sha3/sha3.h"
#include "contrib/hexutils.h"

int main() {
  sha3_ctx *context;
  const unsigned char *msg = "SHA3";

  unsigned int byte_len = sizeof(unsigned char) * sha3_512_hash_size;

  unsigned char *result = malloc(byte_len);
  char *hex = malloc(byte_len);

  size_t len = sizeof(unsigned char) * strlen(msg);

  rhash_sha3_512_init(context);

  rhash_sha3_update(context, msg, len);

  rhash_sha3_final(context, result);

  rhash_byte_to_hex(hex, result, byte_len, 0);

  printf("%s %d %s\n", "SHA: ", byte_len, hex);

  free(result);
  free(hex);
  return 0;
}
