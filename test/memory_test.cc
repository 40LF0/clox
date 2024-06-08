// memory_test.c
// Created by Seungyeon Chung on 2024.06.07.
//
// Test file for memory module.

#include <gtest/gtest.h>

extern "C" {
#include "memory.h"
}

// Test for reallocate function
TEST(MemoryTest, ReallocateTest) {
  // Test reallocation with newSize = 0
  void* ptr1 = malloc(10 * sizeof(int));
  void* result1 = reallocate(ptr1, 10 * sizeof(int), 0);
  ASSERT_EQ(result1, nullptr);

  // Test reallocation with newSize > 0
  void* ptr2 = nullptr;
  void* result2 = reallocate(ptr2, 0, 10 * sizeof(int));
  ASSERT_NE(result2, nullptr);
  free(result2);
}

// Test for GROW_CAPACITY macro
TEST(MemoryTest, GrowCapacityTest) {
  // Test for capacity < 8
  ASSERT_EQ(GROW_CAPACITY(4), 8);

  // Test for capacity >= 8
  ASSERT_EQ(GROW_CAPACITY(10), 20);
}

// Test for GROW_ARRAY macro
TEST(MemoryTest, GrowArrayTest) {
  // Allocate an initial array with capacity 4
  int* arr = GROW_ARRAY(int, nullptr, 0, 4);
  ASSERT_NE(arr, nullptr);

  // Fill the array with some values
  for (int i = 0; i < 4; i++) {
    arr[i] = i * 2;
  }

  // Resize the array to double its capacity
  int* newArr = GROW_ARRAY(int, arr, 4, 8);
  ASSERT_NE(newArr, nullptr);

  // Check if the values are preserved after resizing
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(newArr[i], i * 2);
  }

  // Free the original array and the resized array
  FREE_ARRAY(int, newArr, 8);
}

// Test for FREE_ARRAY macro
TEST(MemoryTest, FreeArrayTest) {
  // Allocate an initial array with capacity 4
  int* arr = GROW_ARRAY(int, nullptr, 0, 4);
  ASSERT_NE(arr, nullptr);

  // Free the array
  FREE_ARRAY(int, arr, 4);

  // Check if the array is successfully freed
  // This test only checks if FREE_ARRAY macro works without runtime errors.
  // Actual memory deallocation is not checked here.
  SUCCEED();
}