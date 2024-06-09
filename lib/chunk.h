// chuck.h
// Created by Seungyeon Chung on 2024.06.07.
//
// This module defines a chunk, which is a sequence of bytecode instructions
// used to represent code in the interpreter.

#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"

// In the bytecode format, each instruction consists of a 1-byte operation code.
// This number represents the type of instruction,
// such as addition, subtraction, variable lookup, etc.
typedef enum { OP_CONSTANT, OP_RETURN } OpCode;

typedef struct {
  int count;             // Number of bytes in the chunk
  int capacity;          // Capacity of the chunk (allocated memory)
  uint8_t *code;         // Array to store bytecodes
  int *lines;            // Array to store line info for each byte in bytecode
  ValueArray constants;  // Array to store values
} Chunk;

void initChunk(Chunk *chuck);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
int addConstant(Chunk *chunk, Value value);

#endif  // CLOX_CHUNK_H