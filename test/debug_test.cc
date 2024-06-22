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

  int constant = addConstant(&chunk, NUMBER_VAL(1.2));
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

  int constant1 = addConstant(&chunk, NUMBER_VAL(1.23));
  int constant2 = addConstant(&chunk, NUMBER_VAL(1.26));

  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant1, 123);
  writeChunk(&chunk, OP_RETURN, 123);
  writeChunk(&chunk, OP_RETURN, 124);
  writeChunk(&chunk, OP_RETURN, 125);
  writeChunk(&chunk, OP_CONSTANT, 126);
  writeChunk(&chunk, constant2, 126);
  writeChunk(&chunk, OP_RETURN, 126);

  testing::internal::CaptureStdout();
  disassembleChunk(&chunk, "integrated_chunk");
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 7);
  EXPECT_EQ(lines[0], "== integrated_chunk ==");
  EXPECT_EQ(lines[1], "0000  123 OP_CONSTANT         0 '1.23'");
  EXPECT_EQ(lines[2], "0002    | OP_RETURN");
  EXPECT_EQ(lines[3], "0003  124 OP_RETURN");
  EXPECT_EQ(lines[4], "0004  125 OP_RETURN");
  EXPECT_EQ(lines[5], "0005  126 OP_CONSTANT         1 '1.26'");
  EXPECT_EQ(lines[6], "0007    | OP_RETURN");

  freeChunk(&chunk);
}

void checkConstantLine(std::vector<std::string>& lines, int& expectOffset,
                       int& line, const char* opCode, const int offset,
                       const int numChunks) {
  char expected[50];
  sprintf(expected, "%04d %4d %-16s %4d '%g'", expectOffset, line, opCode,
          (line * numChunks), (double)(line * numChunks));
  EXPECT_EQ(lines[(line * numChunks) + 1], expected);
  expectOffset += offset;

  for (int i = 1; i < numChunks; ++i) {
    sprintf(expected, "%04d    | %-16s %4d '%g'", expectOffset, opCode,
            (line * numChunks) + i, (double)(line * numChunks) + i);
    EXPECT_EQ(lines[(line * numChunks) + 1 + i], expected);
    expectOffset += offset;
  }
}

TEST(DisassembleChunkTest, WriteConstantTest) {
  Chunk chunk;
  initChunk(&chunk);
  for (int i = 0; i < 512; ++i) {
    int constant = addConstant(&chunk, NUMBER_VAL((double)i));
    writeConstant(&chunk, constant, i / 4);
  }

  testing::internal::CaptureStdout();
  disassembleChunk(&chunk, "constants_chunk");
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 513);
  EXPECT_EQ(lines[0], "== constants_chunk ==");
  int expectOffset = 0;
  int line;
  for (line = 0; line < 256 / 4; ++line) {
    checkConstantLine(lines, expectOffset, line, "OP_CONSTANT", 2, 4);
  }
  for (; line < 512 / 4; ++line) {
    checkConstantLine(lines, expectOffset, line, "OP_CONSTANT_LONG", 4, 4);
  }

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

  int constant = addConstant(&chunk, NUMBER_VAL(1.2));
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

TEST(DisassembleInstructionTest, HandlesConstantLongInstruction) {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, NUMBER_VAL(1.2));
  writeChunk(&chunk, OP_CONSTANT_LONG, 123);
  writeChunk(&chunk, 0, 123);
  writeChunk(&chunk, 0, 123);
  writeChunk(&chunk, constant, 123);

  testing::internal::CaptureStdout();
  int newOffset = disassembleInstruction(&chunk, 0);
  std::vector<std::string> lines = GetCapturedStdoutLines();

  ASSERT_EQ(lines.size(), 1);
  EXPECT_EQ(lines[0], "0000  123 OP_CONSTANT_LONG    0 '1.2'");

  EXPECT_EQ(newOffset, 4);

  freeChunk(&chunk);
}