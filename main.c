// main.c
// Created by Seungyeon Chung on 2024.06.07.
//
// Entry point for the interpreter. This file contains the main function.

#include "common.h"
#include "debug.h"

int main(int argc, const char *argv[]) {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT);
  writeChunk(&chunk, constant);

  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  return 0;
}