// debug_test.c
// Created by Seungyeon Chung on 2024.06.08.
//
// Test file for debug module.

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "unity.h"

#define MAX_LINES 1000
#define LINE_LENGTH 1000

FILE* temp_stdout;
char* stdout_lines[MAX_LINES];
FILE* original_stdout;

void startCaptureStdout(void) {
  original_stdout = stdout;
  temp_stdout = freopen("test_output.txt", "w", stdout);
}

void copyFileToBuffer(void) {
  FILE* file = fopen("test_output.txt", "r");
  if (file == NULL) {
    perror("Failed to open file");
    return;
  }

  char line[LINE_LENGTH];
  int i = 0;
  while (fgets(line, sizeof(line), file) != NULL && i < MAX_LINES) {
    stdout_lines[i] = strdup(line);  // Copy the line to the buffer
    i++;
  }
  fclose(file);
}

void endCaptureStdout(void) {
  fflush(stdout);  // Ensure all output is flushed to the file
  if (temp_stdout != NULL) {
    fclose(temp_stdout);
  }

  freopen("CON", "w", stdout);  // 표준 출력으로 되돌리기 (Windows 시스템)
  copyFileToBuffer();           // 파일에서 버퍼로 데이터를 복사
}

void setUp(void) {}

void tearDown(void) {
  FILE* file = fopen("test_output.txt", "w");
  if (file != NULL) {
    fclose(file);
  }

  for (int i = 0; i < MAX_LINES; i++) {
    if (stdout_lines[i] != NULL) {
      free(stdout_lines[i]);
      stdout_lines[i] = NULL;
    }
  }
}

void test_DisassembleChunk_HandlesEmptyChunk(void) {
  Chunk chunk;
  initChunk(&chunk);
  startCaptureStdout();
  disassembleChunk(&chunk, "empty_chunk");
  endCaptureStdout();

  TEST_ASSERT_EQUAL_STRING("== empty_chunk ==\n", stdout_lines[0]);
  freeChunk(&chunk);
}

void test_DisassembleChunk_HandlesReturnInstruction(void) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, OP_RETURN, 123);
  startCaptureStdout();
  disassembleChunk(&chunk, "return_chunk");
  endCaptureStdout();

  TEST_ASSERT_EQUAL_STRING("== return_chunk ==\n", stdout_lines[0]);
  TEST_ASSERT_EQUAL_STRING("0000  123 OP_RETURN\n", stdout_lines[1]);
  freeChunk(&chunk);
}

void test_DisassembleChunk_HandlesConstantInstruction(void) {
  Chunk chunk;
  initChunk(&chunk);
  int constant = addConstant(&chunk, NUMBER_VAL(1.2));
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  startCaptureStdout();
  disassembleChunk(&chunk, "constant_chunk");
  endCaptureStdout();

  TEST_ASSERT_EQUAL_STRING("== constant_chunk ==\n", stdout_lines[0]);
  TEST_ASSERT_EQUAL_STRING("0000  123 OP_CONSTANT         0 '1.2'\n",
                           stdout_lines[1]);
  freeChunk(&chunk);
}

void test_DisassembleChunk_HandlesMultipleInstructions(void) {
  Chunk chunk;
  initChunk(&chunk);
  int constant = addConstant(&chunk, NUMBER_VAL(1.23));
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  writeChunk(&chunk, OP_RETURN, 123);
  writeChunk(&chunk, OP_RETURN, 124);
  writeChunk(&chunk, OP_RETURN, 125);
  constant = addConstant(&chunk, NUMBER_VAL(1.26));
  writeChunk(&chunk, OP_CONSTANT, 126);
  writeChunk(&chunk, constant, 126);
  writeChunk(&chunk, OP_RETURN, 126);
  startCaptureStdout();
  disassembleChunk(&chunk, "integrated_chunk");
  endCaptureStdout();

  TEST_ASSERT_EQUAL_STRING("== integrated_chunk ==\n", stdout_lines[0]);
  TEST_ASSERT_EQUAL_STRING("0000  123 OP_CONSTANT         0 '1.23'\n",
                           stdout_lines[1]);
  TEST_ASSERT_EQUAL_STRING("0002    | OP_RETURN\n", stdout_lines[2]);
  TEST_ASSERT_EQUAL_STRING("0003  124 OP_RETURN\n", stdout_lines[3]);
  TEST_ASSERT_EQUAL_STRING("0004  125 OP_RETURN\n", stdout_lines[4]);
  TEST_ASSERT_EQUAL_STRING("0005  126 OP_CONSTANT         1 '1.26'\n",
                           stdout_lines[5]);
  TEST_ASSERT_EQUAL_STRING("0007    | OP_RETURN\n", stdout_lines[6]);
  freeChunk(&chunk);
}

void test_DisassembleInstruction_HandlesReturnInstruction(void) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, OP_RETURN, 123);
  startCaptureStdout();
  disassembleInstruction(&chunk, 0);
  endCaptureStdout();

  TEST_ASSERT_EQUAL_STRING("0000  123 OP_RETURN\n", stdout_lines[0]);
  freeChunk(&chunk);
}

void test_DisassembleInstruction_HandlesConstantInstruction(void) {
  Chunk chunk;
  initChunk(&chunk);
  int constant = addConstant(&chunk, NUMBER_VAL(1.2));
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  startCaptureStdout();
  disassembleInstruction(&chunk, 0);
  endCaptureStdout();

  TEST_ASSERT_EQUAL_STRING("0000  123 OP_CONSTANT         0 '1.2'\n",
                           stdout_lines[0]);
  freeChunk(&chunk);
}

void test_DisassembleInstruction_HandlesConstantLongInstruction(void) {
  Chunk chunk;
  initChunk(&chunk);
  int constant = addConstant(&chunk, NUMBER_VAL(1.2));
  writeChunk(&chunk, OP_CONSTANT_LONG, 123);
  writeChunk(&chunk, 0, 123);
  writeChunk(&chunk, 0, 123);
  writeChunk(&chunk, constant, 123);
  startCaptureStdout();
  disassembleInstruction(&chunk, 0);
  endCaptureStdout();

  TEST_ASSERT_EQUAL_STRING("0000  123 OP_CONSTANT_LONG    0 '1.2'\n",
                           stdout_lines[0]);
  freeChunk(&chunk);
}
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_DisassembleChunk_HandlesEmptyChunk);
  RUN_TEST(test_DisassembleChunk_HandlesReturnInstruction);
  RUN_TEST(test_DisassembleChunk_HandlesConstantInstruction);
  RUN_TEST(test_DisassembleChunk_HandlesMultipleInstructions);
  RUN_TEST(test_DisassembleInstruction_HandlesReturnInstruction);
  RUN_TEST(test_DisassembleInstruction_HandlesConstantInstruction);
  RUN_TEST(test_DisassembleInstruction_HandlesConstantLongInstruction);
  return UNITY_END();
}