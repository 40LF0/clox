// debug_test.cc
// Created by Seungyeon Chung on 2024.06.08.
//
// Test file for debug module.

#include <gtest/gtest.h>

#include <string>

extern "C" {
#include "chunk.h"
#include "debug.h"
}

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
  disassembleChunk(&chunk, "empty_chunk");
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 1);
  EXPECT_EQ(lines[0], "== empty_chunk ==");
}

TEST(DisassembleChunkTest, HandlesReturnInstruction) {
  Chunk chunk;
  initChunk(&chunk);

  writeChunk(&chunk, OP_RETURN, 123);

  testing::internal::CaptureStdout();
  disassembleChunk(&chunk, "return_chunk");
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 2);
  EXPECT_EQ(lines[0], "== return_chunk ==");
  EXPECT_EQ(lines[1], "0000  123 OP_RETURN");

  freeChunk(&chunk);
}

TEST(DisassembleChunkTest, HandlesConstantInstruction) {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  testing::internal::CaptureStdout();
  disassembleChunk(&chunk, "constant_chunk");
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 2);
  EXPECT_EQ(lines[0], "== constant_chunk ==");
  EXPECT_EQ(lines[1], "0000  123 OP_CONSTANT         0 '1.2'");

  freeChunk(&chunk);
}

TEST(DisassembleChunkTest, HandlesMultipleInstructions) {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  writeChunk(&chunk, OP_RETURN, 123);

  testing::internal::CaptureStdout();
  disassembleChunk(&chunk, "integrated_chunk");
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 3);
  EXPECT_EQ(lines[0], "== integrated_chunk ==");
  EXPECT_EQ(lines[1], "0000  123 OP_CONSTANT         0 '1.2'");
  EXPECT_EQ(lines[2], "0002    | OP_RETURN");

  freeChunk(&chunk);
}

TEST(DisassembleInstructionTest, HandlesReturnInstruction) {
  Chunk chunk;
  initChunk(&chunk);

  writeChunk(&chunk, OP_RETURN, 123);

  testing::internal::CaptureStdout();
  int newOffset = disassembleInstruction(&chunk, 0);
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 1);
  EXPECT_EQ(lines[0], "0000  123 OP_RETURN");

  EXPECT_EQ(newOffset, 1);

  freeChunk(&chunk);
}

TEST(DisassembleInstructionTest, HandlesConstantInstruction) {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  testing::internal::CaptureStdout();
  int newOffset = disassembleInstruction(&chunk, 0);
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 1);
  EXPECT_EQ(lines[0], "0000  123 OP_CONSTANT         0 '1.2'");

  EXPECT_EQ(newOffset, 2);

  freeChunk(&chunk);
}