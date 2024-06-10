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


  writeConstant(&chunk, 1.23, 123);
  writeChunk(&chunk, OP_RETURN, 123);

  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}