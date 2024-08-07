// value_test.c
// Created by Seungyeon Chung on 2024.06.09.
//
// Test file for value module.

#include "value.h"

#include <memory.h>

#include "object.h"
#include "unity.h"
#include "vm.h"

Value TEST_CONSTANT;
Value TEST_BOOL_TRUE;
Value TEST_BOOL_FALSE;
Value TEST_NIL;
Value TEST_OBJ;

void setUp(void) {
  initVM();
  ObjString* objString = copyString("test", 4);
  TEST_OBJ = OBJ_VAL(objString);

  TEST_CONSTANT = NUMBER_VAL(1.2);
  TEST_BOOL_TRUE = BOOL_VAL(true);
  TEST_BOOL_FALSE = BOOL_VAL(false);
  TEST_NIL = NIL_VAL;
}

void tearDown(void) {
  freeVM();
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
  TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(TEST_CONSTANT),
                           AS_NUMBER(valueArray.values[0]));
  freeValueArray(&valueArray);
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
  TEST_ASSERT_TRUE(valueArray.capacity >= 1);
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
  TEST_ASSERT_TRUE(valueArray.capacity >= 9);
  for (int i = 0; i < 9; ++i) {
    TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(valueArray.values[i]), (double)i);
  }
  freeValueArray(&valueArray);
}

void test_ValueArray_WriteDifferentTypes(void) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  writeValueArray(&valueArray, TEST_CONSTANT);
  writeValueArray(&valueArray, TEST_BOOL_TRUE);
  writeValueArray(&valueArray, TEST_NIL);
  writeValueArray(&valueArray, TEST_OBJ);

  TEST_ASSERT_EQUAL_INT(4, valueArray.count);
  TEST_ASSERT_TRUE(valueArray.capacity >= 3);
  TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(valueArray.values[0]),
                           AS_NUMBER(TEST_CONSTANT));
  TEST_ASSERT_EQUAL(AS_BOOL(valueArray.values[1]), AS_BOOL(TEST_BOOL_TRUE));
  TEST_ASSERT_EQUAL_INT(valueArray.values[2].type, VAL_NIL);
  TEST_ASSERT_EQUAL_PTR(AS_OBJ(valueArray.values[3]), AS_OBJ(TEST_OBJ));

  freeValueArray(&valueArray);
}

void test_ValueArray_BoundaryConditions(void) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  for (int i = 0; i < 10000000; ++i) {
    writeValueArray(&valueArray, NUMBER_VAL((double)i));
  }
  TEST_ASSERT_EQUAL_INT(10000000, valueArray.count);
  TEST_ASSERT_TRUE(valueArray.capacity >= 10000000);
  for (int i = 0; i < 10000000; ++i) {
    TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(valueArray.values[i]), (double)i);
  }
  freeValueArray(&valueArray);
}

void test_valuesEqual(void) {
  TEST_ASSERT_TRUE(valuesEqual(TEST_CONSTANT, NUMBER_VAL(1.2)));
  TEST_ASSERT_FALSE(valuesEqual(TEST_CONSTANT, NUMBER_VAL(2.3)));
  TEST_ASSERT_TRUE(valuesEqual(TEST_BOOL_TRUE, BOOL_VAL(true)));
  TEST_ASSERT_FALSE(valuesEqual(TEST_BOOL_TRUE, BOOL_VAL(false)));
  TEST_ASSERT_TRUE(valuesEqual(TEST_NIL, NIL_VAL));
  TEST_ASSERT_FALSE(valuesEqual(TEST_NIL, BOOL_VAL(false)));

  ObjString* string1 = copyString("test", 4);
  Value obj1 = OBJ_VAL(string1);
  TEST_ASSERT_TRUE(valuesEqual(TEST_OBJ, obj1));

  ObjString* string2 = copyString("diff", 4);
  Value obj2 = OBJ_VAL(string2);
  TEST_ASSERT_FALSE(valuesEqual(TEST_OBJ, obj2));
}

void test_IS_BOOL(void) {
  TEST_ASSERT_TRUE(IS_BOOL(TEST_BOOL_TRUE));
  TEST_ASSERT_FALSE(IS_BOOL(TEST_CONSTANT));
  TEST_ASSERT_FALSE(IS_BOOL(TEST_NIL));
  TEST_ASSERT_FALSE(IS_BOOL(TEST_OBJ));
}

void test_IS_NIL(void) {
  TEST_ASSERT_TRUE(IS_NIL(TEST_NIL));
  TEST_ASSERT_FALSE(IS_NIL(TEST_CONSTANT));
  TEST_ASSERT_FALSE(IS_NIL(TEST_BOOL_TRUE));
  TEST_ASSERT_FALSE(IS_NIL(TEST_OBJ));
}

void test_IS_NUMBER(void) {
  TEST_ASSERT_TRUE(IS_NUMBER(TEST_CONSTANT));
  TEST_ASSERT_FALSE(IS_NUMBER(TEST_BOOL_TRUE));
  TEST_ASSERT_FALSE(IS_NUMBER(TEST_NIL));
  TEST_ASSERT_FALSE(IS_NUMBER(TEST_OBJ));
}

void test_IS_OBJ(void) {
  TEST_ASSERT_TRUE(IS_OBJ(TEST_OBJ));
  TEST_ASSERT_FALSE(IS_OBJ(TEST_CONSTANT));
  TEST_ASSERT_FALSE(IS_OBJ(TEST_BOOL_TRUE));
  TEST_ASSERT_FALSE(IS_OBJ(TEST_NIL));
}

void test_AS_BOOL(void) {
  TEST_ASSERT_EQUAL(AS_BOOL(TEST_BOOL_TRUE), true);
  TEST_ASSERT_EQUAL(AS_BOOL(TEST_BOOL_FALSE), false);
}

void test_AS_NUMBER(void) {
  TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(TEST_CONSTANT), 1.2);
}

void test_AS_OBJ(void) {
  TEST_ASSERT_EQUAL_PTR(AS_OBJ(TEST_OBJ), AS_OBJ(TEST_OBJ));
}

void test_BOOL_VAL(void) {
  Value boolValue = BOOL_VAL(true);
  TEST_ASSERT_TRUE(IS_BOOL(boolValue));
  TEST_ASSERT_EQUAL(AS_BOOL(boolValue), true);
}

void test_NIL_VAL(void) {
  Value nilValue = NIL_VAL;
  TEST_ASSERT_TRUE(IS_NIL(nilValue));
}

void test_NUMBER_VAL(void) {
  Value numberValue = NUMBER_VAL(3.4);
  TEST_ASSERT_TRUE(IS_NUMBER(numberValue));
  TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(numberValue), 3.4);

  // Boundary value test for NUMBER_VAL macro
  Value largeNumberValue = NUMBER_VAL(1e308);
  TEST_ASSERT_TRUE(IS_NUMBER(largeNumberValue));
  TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(largeNumberValue), 1e308);

  Value smallNumberValue = NUMBER_VAL(1e-308);
  TEST_ASSERT_TRUE(IS_NUMBER(smallNumberValue));
  TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(smallNumberValue), 1e-308);
}

void test_OBJ_VAL(void) {
  Value objValue = TEST_OBJ;
  TEST_ASSERT_TRUE(IS_OBJ(objValue));
  TEST_ASSERT_EQUAL_PTR(AS_OBJ(objValue), AS_OBJ(TEST_OBJ));
}

void test_ErrorHandling(void) {
  // Error handling tests
  Value mixedValue;
  mixedValue.type = VAL_BOOL;
  mixedValue.as.boolean = true;  // Correct usage
  TEST_ASSERT_FALSE(IS_NUMBER(mixedValue));
  TEST_ASSERT_TRUE(IS_BOOL(mixedValue));  // Still should be recognized as bool

  mixedValue.type = VAL_NUMBER;
  mixedValue.as.number = 1.2;  // Correct usage
  TEST_ASSERT_TRUE(IS_NUMBER(mixedValue));
  TEST_ASSERT_EQUAL_DOUBLE(AS_NUMBER(mixedValue), 1.2);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_ValueArray_InitValueArray);
  RUN_TEST(test_ValueArray_WriteValueArray);
  RUN_TEST(test_ValueArray_FreeValueArray);
  RUN_TEST(test_ValueArray_WriteValueArrayInitialCapacity);
  RUN_TEST(test_ValueArray_WriteValueArrayDoubleCapacity);
  RUN_TEST(test_ValueArray_WriteDifferentTypes);
  RUN_TEST(test_ValueArray_BoundaryConditions);
  RUN_TEST(test_valuesEqual);
  RUN_TEST(test_IS_BOOL);
  RUN_TEST(test_IS_NIL);
  RUN_TEST(test_IS_NUMBER);
  RUN_TEST(test_IS_OBJ);
  RUN_TEST(test_AS_BOOL);
  RUN_TEST(test_AS_NUMBER);
  RUN_TEST(test_AS_OBJ);
  RUN_TEST(test_BOOL_VAL);
  RUN_TEST(test_NIL_VAL);
  RUN_TEST(test_NUMBER_VAL);
  RUN_TEST(test_OBJ_VAL);
  RUN_TEST(test_ErrorHandling);
  return UNITY_END();
}
