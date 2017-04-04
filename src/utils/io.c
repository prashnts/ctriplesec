#include "io.h"

void print_bytearray(void *buffer, int buffer_len) {
  char *dest = malloc(buffer_len * 2);
  rhash_byte_to_hex(dest, buffer, buffer_len, 0);
  printf("%s\n", dest);
  free(dest);
}
