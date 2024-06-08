// debug_test.cc
// Created by Seungyeon Chung on 2024.06.08.
//
// Test file for debug module.

#include <gtest/gtest.h>
#include <string>

#include "chuck.h"
#include "debug.h"

std::vector<std::string> GetCapturedStdoutLines() {
  std::string output = testing::internal::GetCapturedStdout();

  std::stringstream ss(output);
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(ss, line, '\n')) {
    lines.push_back(line);
  }
  return lines;
}

TEST(DisassembleChunkTest, HandlesEmptyChunk) {
  Chunk chunk;
  initChunk(&chunk);

  testing::internal::CaptureStdout();
  disassembleChunk(&chunk, "test_chunk");
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 1);
  EXPECT_EQ(lines[0], "== test_chunk ==");
}

TEST(DisassembleChunkTest, HandlesReturnInstruction) {
  Chunk chunk;
  initChunk(&chunk);

  writeChunk(&chunk, OP_RETURN);

  testing::internal::CaptureStdout();
  disassembleChunk(&chunk, "test_chunk");
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 2);
  EXPECT_EQ(lines[0], "== test_chunk ==");
  EXPECT_EQ(lines[1], "0000 OP_RETURN");

  freeChunk(&chunk);
}

TEST(DisassembleInstructionTest, HandlesReturnInstruction) {
  Chunk chunk;
  initChunk(&chunk);

  writeChunk(&chunk, OP_RETURN);

  testing::internal::CaptureStdout();
  int newOffset = disassembleInstruction(&chunk, 0);
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 1);
  EXPECT_EQ(lines[0], "0000 OP_RETURN");

  EXPECT_EQ(newOffset, 1);

  freeChunk(&chunk);
}