// chuck.h
// Created by Seungyeon Chung on 2024.06.07.
//
// This module defines a chunk, which is a sequence of bytecode instructions
// used to represent code in the interpreter.

#ifndef CLOX_CHUCK_H
#define CLOX_CHUCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

// In the bytecode format, each instruction consists of a 1-byte operation code.
// This number represents the type of instruction,
// such as addition, subtraction, variable lookup, etc.
typedef enum { OP_RETURN } OpCode;

typedef struct {
  int count;         // Number of bytes in the chunk
  int capacity;      // Capacity of the chunk (allocated memory)
  uint8_t* code;     // Array to store bytecodes
} Chunk;

void initChunk(Chunk* chuck);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);


#ifdef __cplusplus
}
#endif

#endif // CLOX_CHUCK_H
