// chunk_test.c
// Created by Seungyeon Chung on 2024.06.08.
//
// Test file for chunk module.

#include "chunk.h"

#include "unity.h"

void setUp(void) {
  // 추가 초기화 코드가 필요하면 여기에 작성
}

void tearDown(void) {
  // 추가 정리 코드가 필요하면 여기에 작성
}

void test_Chunk_InitChunk(void) {
  Chunk chunk;
  initChunk(&chunk);
  TEST_ASSERT_EQUAL_INT(0, chunk.count);
  TEST_ASSERT_EQUAL_INT(0, chunk.capacity);
  TEST_ASSERT_NULL(chunk.code);
}

void test_Chunk_WriteChunk(void) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, 1, 123);
  TEST_ASSERT_EQUAL_INT(1, chunk.count);
  TEST_ASSERT_TRUE(chunk.capacity >= 1);
  TEST_ASSERT_EQUAL_INT(1, chunk.code[0]);
  freeChunk(&chunk);
}

void test_Chunk_FreeChunk(void) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, 1, 123);
  freeChunk(&chunk);
  TEST_ASSERT_EQUAL_INT(0, chunk.count);
  TEST_ASSERT_EQUAL_INT(0, chunk.capacity);
  TEST_ASSERT_NULL(chunk.code);
}

void test_Chunk_WriteChunkInitialCapacity(void) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, 1, 123);
  TEST_ASSERT_EQUAL_INT(1, chunk.count);
  TEST_ASSERT_EQUAL_INT(8, chunk.capacity);
  TEST_ASSERT_EQUAL_INT(1, chunk.code[0]);
  freeChunk(&chunk);
}

void test_Chunk_WriteChunkDoubleCapacity(void) {
  Chunk chunk;
  initChunk(&chunk);
  for (int i = 0; i < 9; ++i) {
    writeChunk(&chunk, i, 123);
  }
  TEST_ASSERT_EQUAL_INT(9, chunk.count);
  TEST_ASSERT_EQUAL_INT(16, chunk.capacity);
  for (int i = 0; i < 9; ++i) {
    TEST_ASSERT_EQUAL_INT(chunk.code[i], i);
  }
  freeChunk(&chunk);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_Chunk_InitChunk);
  RUN_TEST(test_Chunk_WriteChunk);
  RUN_TEST(test_Chunk_FreeChunk);
  RUN_TEST(test_Chunk_WriteChunkInitialCapacity);
  RUN_TEST(test_Chunk_WriteChunkDoubleCapacity);
  return UNITY_END();
}
