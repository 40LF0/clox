// vm.h
// Created by Seungyeon Chung on 2024.06.09.
//
// A virtual machine is a component that interprets and executes chunks of code.

#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"

typedef struct {
  Chunk* chunk;
  uint8_t* ip;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);

#endif  // CLOX_VM_H
