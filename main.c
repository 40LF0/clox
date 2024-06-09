// main.c
// Created by Seungyeon Chung on 2024.06.07.
//
// Entry point for the interpreter. This file contains the main function.

#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  for (int i = 0; i < 300; ++i) {
    writeConstant(&chunk, (double)i / 10, i / 4);
  }
  writeChunk(&chunk, OP_RETURN, 75);

  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}