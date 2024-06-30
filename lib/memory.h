// memory.h
// Created by Seungyeon Chung on 2024.06.07.
//
// This module is responsible for low-level memory operations.

#ifndef CLOX_MEMORY_H
#define CLOX_MEMORY_H

#include "common.h"

#define ALLOCATE(type, count) \
  (type *)reallocate(NULL, 0, sizeof(type) * (count))

#define FREE(type, pointer) reallocate(pointer, sizeof(type), 0)

#define MIN_CAPACITY 8

#define GROW_CAPACITY(capacity) \
  ((capacity) < MIN_CAPACITY ? MIN_CAPACITY : (capacity) * 2)

#define SHRINK_CAPACITY(capacity, minCapacity) \
  ((capacity) <= minCapacity ? capacity : (capacity) / 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount)    \
  (type *)reallocate(pointer, sizeof(type) * (oldCount), \
                     sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
  (type *)reallocate(pointer, sizeof(type) * (oldCount), 0)

void *reallocate(void *pointer, size_t oldSize, size_t newSize);
void *freeObjects();

#endif  // CLOX_MEMORY_H