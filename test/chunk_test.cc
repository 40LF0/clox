// chunk_test.cc
// Created by Seungyeon Chung on 2024.06.08.
//
// Test file for chunk module.

#include <gtest/gtest.h>

extern "C" {
#include "chunk.h"
}

TEST(ChunkTest, InitChunk) {
  Chunk chunk;
  initChunk(&chunk);
  EXPECT_EQ(0, chunk.count);
  EXPECT_EQ(0, chunk.capacity);
  EXPECT_EQ(nullptr, chunk.code);
}

TEST(ChunkTest, WriteChunk) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, 1, 123);
  EXPECT_EQ(1, chunk.count);
  EXPECT_LE(1, chunk.capacity);
  EXPECT_EQ(1, chunk.code[0]);
  freeChunk(&chunk);
}

TEST(ChunkTest, FreeChunk) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, 1, 123);
  freeChunk(&chunk);
  EXPECT_EQ(0, chunk.count);
  EXPECT_EQ(0, chunk.capacity);
  EXPECT_EQ(nullptr, chunk.code);
}

TEST(ChunkTest, WriteChunkInitialCapacity) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, 1, 123);
  EXPECT_EQ(1, chunk.count);
  EXPECT_EQ(8, chunk.capacity);
  EXPECT_EQ(1, chunk.code[0]);
  freeChunk(&chunk);
}

TEST(ChunkTest, WriteChunkDoubleCapacity) {
  Chunk chunk;
  initChunk(&chunk);
  for (int i = 0; i < 9; ++i) {
    writeChunk(&chunk, i, 123);
  }
  EXPECT_EQ(9, chunk.count);
  EXPECT_EQ(16, chunk.capacity);
  for (int i = 0; i < 9; ++i) {
    EXPECT_EQ(chunk.code[i], i);
  }
  freeChunk(&chunk);
}