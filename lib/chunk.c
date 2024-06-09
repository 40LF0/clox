// chuck.c
// Created by Seungyeon Chung on 2024.06.07.
//
// This module defines a chunk, which is a sequence of bytecode instructions
// used to represent code in the interpreter.

#include "chunk.h"

#include <stdlib.h>

#include "memory.h"

void initLineArray(LineArray *array) {
  array->count = 0;
  array->capacity = 0;
  array->runs = NULL;
}

void freeLineArray(LineArray *array) {
  FREE_ARRAY(LineRun, array->runs, array->capacity);
  initLineArray(array);
}

void writeLineArray(LineArray *array, int line) {
  if (array->count == 0 || array->runs[array->count - 1].line != line) {
    if (array->capacity < array->count + 1) {
      int oldCapacity = array->capacity;
      array->capacity = GROW_CAPACITY(oldCapacity);
      array->runs =
          GROW_ARRAY(LineRun, array->runs, oldCapacity, array->capacity);
    }
    array->runs[array->count].line = line;
    array->runs[array->count].runLength = 1;
    array->count++;
  } else {
    array->runs[array->count - 1].runLength++;
  }
}

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  initLineArray(&chunk->lines);
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  freeLineArray(&chunk->lines);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code =
        GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
  }
  writeLineArray(&chunk->lines, line);

  chunk->code[chunk->count] = byte;
  chunk->count++;
}

void writeConstant(Chunk *chunk, Value value, int line) {
  int constant = addConstant(chunk, value);
  if (constant < 256) {
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, (uint8_t)constant, line);
  } else {
    writeChunk(chunk, OP_CONSTANT_LONG, line);
    writeChunk(chunk, (uint8_t)(constant >> 16), line);
    writeChunk(chunk, (uint8_t)(constant >> 8), line);
    writeChunk(chunk, (uint8_t)constant, line);
  }
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

int getLine(Chunk *chunk, int offset) {
  int currentOffset = 0;
  for (int i = 0; i < chunk->lines.count; i++) {
    currentOffset += chunk->lines.runs[i].runLength;
    if (currentOffset > offset) {
      return chunk->lines.runs[i].line;
    }
  }
  return -1;  // Should not reach here if the offset is valid
}
