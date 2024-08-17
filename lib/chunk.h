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
typedef enum {
  OP_CONSTANT,
  OP_CONSTANT_LONG,
  OP_NIL,
  OP_TRUE,
  OP_FALSE,
  OP_POP,
  OP_DOUBLE_POP,
  OP_COMPARE,
  OP_SET_LOCAL,
  OP_GET_LOCAL,
  OP_GET_GLOBAL,
  OP_DEFINE_GLOBAL,
  OP_SET_GLOBAL,
  OP_GET_UPVALUE,
  OP_SET_UPVALUE,
  OP_GET_PROPERTY,
  OP_SET_PROPERTY,
  OP_GET_SUPER,
  OP_EQUAL,
  OP_GREATER,
  OP_LESS,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NOT,
  OP_NEGATE,
  OP_PRINT,
  OP_JUMP,
  OP_JUMP_IF_FALSE,
  OP_LOOP,
  OP_CALL,
  OP_INVOKE,
  OP_SUPER_INVOKE,
  OP_CLOSURE,
  OP_CLOSURE_LONG,
  OP_CLOSE_UPVALUE,
  OP_RETURN,
  OP_CLASS,
  OP_INHERIT,
  OP_METHOD,
} OpCode;

typedef struct {
  int line;       // line numbers
  int runLength;  // run lengths
} LineRun;

typedef struct {
  int count;      // Number of LineRun entries
  int capacity;   // Capacity of the runs array
  LineRun *runs;  // Array to store run-length encoded line info
} LineArray;

typedef struct {
  int count;             // Number of bytes in the chunk
  int capacity;          // Capacity of the chunk (allocated memory)
  uint8_t *code;         // Array to store bytecodes
  LineArray lines;       // Array to store line info for each byte in bytecode
  ValueArray constants;  // Array to store values
} Chunk;

void initLineArray(LineArray *array);
void writeLineArray(LineArray *array, int line);
void freeLineArray(LineArray *array);

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
void writeConstant(Chunk *chunk, int constant, int line);
void writeClosure(Chunk *chunk, int constant, int line);
int addConstant(Chunk *chunk, Value value);
int getLine(Chunk *chunk, int offset);

#endif  // CLOX_CHUNK_H