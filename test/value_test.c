// value_test.c
// Created by Seungyeon Chung on 2024.06.09.
//
// Test file for value module.

#include "value.h"

#include "unity.h"

Value TEST_CONSTANT = NUMBER_VAL(1.2);

void setUp(void) {
  // 추가 초기화 코드가 필요하면 여기에 작성
}

void tearDown(void) {
  // 추가 정리 코드가 필요하면 여기에 작성
}

void test_ValueArray_InitValueArray(void) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  TEST_ASSERT_EQUAL_INT(0, valueArray.count);
  TEST_ASSERT_EQUAL_INT(0, valueArray.capacity);
  TEST_ASSERT_NULL(valueArray.values);
}

void test_ValueArray_WriteValueArray(void) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  writeValueArray(&valueArray, TEST_CONSTANT);
  TEST_ASSERT_EQUAL_INT(1, valueArray.count);
  TEST_ASSERT_TRUE(valueArray.capacity >= 1);
#define UNITY_INCLUDE_DOUBLE
  TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(TEST_CONSTANT),
                           AS_NUMBER(valueArray.values[0]));
  freeValueArray(&valueArray);
#undef UNITY_INCLUDE_DOUBLE
}

void test_ValueArray_FreeValueArray(void) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  writeValueArray(&valueArray, TEST_CONSTANT);
  freeValueArray(&valueArray);
  TEST_ASSERT_EQUAL_INT(0, valueArray.count);
  TEST_ASSERT_EQUAL_INT(0, valueArray.capacity);
  TEST_ASSERT_NULL(valueArray.values);
}

void test_ValueArray_WriteValueArrayInitialCapacity(void) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  writeValueArray(&valueArray, TEST_CONSTANT);
  TEST_ASSERT_EQUAL_INT(1, valueArray.count);
  TEST_ASSERT_EQUAL_INT(8, valueArray.capacity);
  TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(TEST_CONSTANT),
                           AS_NUMBER(valueArray.values[0]));
  freeValueArray(&valueArray);
}

void test_ValueArray_WriteValueArrayDoubleCapacity(void) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  for (int i = 0; i < 9; ++i) {
    writeValueArray(&valueArray, NUMBER_VAL((double)i));
  }
  TEST_ASSERT_EQUAL_INT(9, valueArray.count);
  TEST_ASSERT_EQUAL_INT(16, valueArray.capacity);
  for (int i = 0; i < 9; ++i) {
    TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(valueArray.values[i]), (double)i);
  }
  freeValueArray(&valueArray);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_ValueArray_InitValueArray);
  RUN_TEST(test_ValueArray_WriteValueArray);
  RUN_TEST(test_ValueArray_FreeValueArray);
  RUN_TEST(test_ValueArray_WriteValueArrayInitialCapacity);
  RUN_TEST(test_ValueArray_WriteValueArrayDoubleCapacity);
    return UNITY_END();
}
