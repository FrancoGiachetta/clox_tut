#include "../include/memory.h"
#include <stdlib.h>

void *reallocate(void *ptr, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(ptr);
    return NULL;
  }

  void *new_ptr = realloc(ptr, newSize);

  if (new_ptr == NULL)
    exit(1);

  return new_ptr;
}
