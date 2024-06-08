// value.h
// Created by Seungyeon Chung on 2024.06.08.
//
// This module defines a value, which is literal constant.
// The immediate instruction following the opcode points to this value.

#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H

#include "common.h"

typedef double Value;

typedef struct {
  int capacity;   // Capacity of the valueArray (allocated memory)
  int count;      // Number of values in the valueArray
  Value* values;  // Array to store values
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif  // CLOX_VALUE_H
