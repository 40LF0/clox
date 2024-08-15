// vm.h
// Created by Seungyeon Chung on 2024.06.09.
//
// A virtual machine is a component that interprets and executes chunks of code.

#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define VM_STACK_MIN_CAPACITY 256
#define FRAMES_MAX 256
#define STACK_MAX (FRAME_MAX * UINT8_COUNT)

typedef struct {
  ObjClosure* closure;
  uint8_t* ip;
  Value* slots;
} CallFrame;

typedef struct {
  CallFrame frames[FRAMES_MAX];
  int frameCount;

  Chunk* chunk;
  uint8_t* ip;
  int stackCapacity;
  Value* stack;
  Value* stackTop;
  Table globals;
  Table strings;
  ObjString* initString;
  ObjUpvalue* openUpvalues;

  size_t bytesAllocated;
  size_t nextGC;
  Obj* objects;
  int grayCount;
  int grayCapacity;
  Obj** grayStack;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif  // CLOX_VM_H
