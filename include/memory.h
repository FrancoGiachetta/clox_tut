#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) capacity < 8 ? 8 : capacity * 2
#define GROW_ARRAY(type, ptr, oldCapacity, capacity)                                                                   \
    (type *)reallocate(ptr, sizeof(type) * oldCapacity, sizeof(type) * capacity)
#define FREE_ARRAY(type, ptr, oldCapacity) reallocate(ptr, sizeof(type) * oldCapacity, 0)

void *reallocate(void *ptr, size_t oldSize, size_t newSize);

#endif
