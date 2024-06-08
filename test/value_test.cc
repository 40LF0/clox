// value_test.cc
// Created by Seungyeon Chung on 2024.06.09.
//
// Test file for value module.

#include <gtest/gtest.h>

extern "C" {
#include "value.h"
}

double TEST_CONSTANT = 1.2;

TEST(ValueArrayTest, InitValueArray) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  EXPECT_EQ(0, valueArray.count);
  EXPECT_EQ(0, valueArray.capacity);
  EXPECT_EQ(nullptr, valueArray.values);
}

TEST(ValueArrayTest, WriteValueArray) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  writeValueArray(&valueArray, TEST_CONSTANT);
  EXPECT_EQ(1, valueArray.count);
  EXPECT_LE(1, valueArray.capacity);
  EXPECT_EQ(TEST_CONSTANT, valueArray.values[0]);
  freeValueArray(&valueArray);
}

TEST(ValueArrayTest, FreeValueArray) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  writeValueArray(&valueArray, TEST_CONSTANT);
  freeValueArray(&valueArray);
  EXPECT_EQ(0, valueArray.count);
  EXPECT_EQ(0, valueArray.capacity);
  EXPECT_EQ(nullptr, valueArray.values);
}

TEST(ValueArrayTest, WriteValueArrayInitialCapacity) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  writeValueArray(&valueArray, TEST_CONSTANT);
  EXPECT_EQ(1, valueArray.count);
  EXPECT_EQ(8, valueArray.capacity);
  EXPECT_EQ(TEST_CONSTANT, valueArray.values[0]);
  freeValueArray(&valueArray);
}

TEST(ValueArrayTest, WriteValueArrayDoubleCapacity) {
  ValueArray valueArray;
  initValueArray(&valueArray);
  for (int i = 0; i < 9; ++i) {
    writeValueArray(&valueArray, (double)i);
  }
  EXPECT_EQ(9, valueArray.count);
  EXPECT_EQ(16, valueArray.capacity);
  for (int i = 0; i < 9; ++i) {
    EXPECT_EQ(valueArray.values[i], (double)i);
  }
  freeValueArray(&valueArray);
}