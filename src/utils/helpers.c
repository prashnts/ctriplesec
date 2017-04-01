#include "helpers.h"

/**
 * Compare byte array for element wise equality. A return value of 0 indicates
 * that x and y are equal.
 */
int mem_isequal(const uint8_t *x, const uint8_t *y, size_t sz) {
  size_t i;
  int rv = -1 ;

  if ((sz > 0) && (x != NULL) && (y != NULL)) {
    for (i = 0, rv = 0; i < sz; i++) {
      rv |= (x[i] ^ y[i]);
    }
  }

  return rv;
}
