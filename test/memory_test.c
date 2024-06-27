// memory_test.c
// Created by Seungyeon Chung on 2024.06.07.
//
// Test file for memory module.

#include "unity.h"
#include "memory.h"
#include <stdlib.h>

void setUp(void) {
    // 추가 초기화 코드가 필요하면 여기에 작성
}

void tearDown(void) {
    // 추가 정리 코드가 필요하면 여기에 작성
}

void test_Memory_ReallocateTest(void) {
    // Test reallocation with newSize = 0
    void* ptr1 = malloc(10 * sizeof(int));
    void* result1 = reallocate(ptr1, 10 * sizeof(int), 0);
    TEST_ASSERT_NULL(result1);

    // Test reallocation with newSize > 0
    void* ptr2 = NULL;
    void* result2 = reallocate(ptr2, 0, 10 * sizeof(int));
    TEST_ASSERT_NOT_NULL(result2);
    free(result2);
}

void test_Memory_GrowCapacityTest(void) {
    // Test for capacity < 8
    TEST_ASSERT_EQUAL_INT(8, GROW_CAPACITY(4));

    // Test for capacity >= 8
    TEST_ASSERT_EQUAL_INT(20, GROW_CAPACITY(10));
}

void test_Memory_GrowArrayTest(void) {
    // Allocate an initial array with capacity 4
    int* arr = GROW_ARRAY(int, NULL, 0, 4);
    TEST_ASSERT_NOT_NULL(arr);

    // Fill the array with some values
    for (int i = 0; i < 4; i++) {
        arr[i] = i * 2;
    }

    // Resize the array to double its capacity
    int* newArr = GROW_ARRAY(int, arr, 4, 8);
    TEST_ASSERT_NOT_NULL(newArr);

    // Check if the values are preserved after resizing
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL_INT(newArr[i], i * 2);
    }

    // Free the original array and the resized array
    FREE_ARRAY(int, newArr, 8);
}

void test_Memory_FreeArrayTest(void) {
    // Allocate an initial array with capacity 4
    int* arr = GROW_ARRAY(int, NULL, 0, 4);
    TEST_ASSERT_NOT_NULL(arr);

    // Free the array
    FREE_ARRAY(int, arr, 4);

    // Check if the array is successfully freed
    // This test only checks if FREE_ARRAY macro works without runtime errors.
    // Actual memory deallocation is not checked here.
    TEST_ASSERT_TRUE(1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Memory_ReallocateTest);
    RUN_TEST(test_Memory_GrowCapacityTest);
    RUN_TEST(test_Memory_GrowArrayTest);
    RUN_TEST(test_Memory_FreeArrayTest);
    return UNITY_END();
}
