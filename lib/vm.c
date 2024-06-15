// VM.c
// Created by Seungyeon Chung on 2024.06.09.
//
// A virtual machine is a component that interprets and executes chunks of code.

#include "vm.h"

#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "memory.h"

VM vm;

static void initStack() {
  vm.stackCapacity = GROW_CAPACITY(VM_STACK_MIN_CAPACITY);
  vm.stack = GROW_ARRAY(Value, vm.stack, 0, vm.stackCapacity);
  vm.stackTop = vm.stack;
}

static void freeStack() {
  FREE_ARRAY(Value, vm.stack, vm.stackCapacity);
  vm.stack = NULL;
  vm.stackCapacity = 0;
  vm.stackTop = NULL;
}

void initVM() { initStack(); }

void freeVM() { freeStack(); }

void push(Value value) {
  long long offset = vm.stackTop - vm.stack;

  if (offset >= (vm.stackCapacity - 1)) {
    int oldCapacity = vm.stackCapacity;
    vm.stackCapacity = GROW_CAPACITY(oldCapacity);
    vm.stack = GROW_ARRAY(Value, vm.stack, oldCapacity, vm.stackCapacity);
    vm.stackTop = vm.stack + offset;
  }

  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  long long offset = vm.stackTop - vm.stack;
  int minCapacity = GROW_CAPACITY(VM_STACK_MIN_CAPACITY);

  if (vm.stackCapacity > minCapacity && offset <= (vm.stackCapacity / 4)) {
    int oldCapacity = vm.stackCapacity;
    vm.stackCapacity = SHRINK_CAPACITY(oldCapacity, minCapacity);
    vm.stack = GROW_ARRAY(Value, vm.stack, oldCapacity, vm.stackCapacity);
    vm.stackTop = vm.stack + offset;
  }

  vm.stackTop--;
  return *vm.stackTop;
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define READ_CONSTANT_LONG() \
  (vm.chunk->constants       \
       .values[READ_BYTE() << 16 | READ_BYTE() << 8 | READ_BYTE()])
#define BINARY_OP(op) \
  do {                \
    double b = pop(); \
    double a = pop(); \
    push(a op b);     \
  } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("        ");
    for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
      case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        push(constant);
        break;
      }
      case OP_CONSTANT_LONG: {
        Value constant = READ_CONSTANT_LONG();
        push(constant);
        break;
      }
      case OP_ADD:
        BINARY_OP(+);
        break;
      case OP_SUBTRACT:
        BINARY_OP(-);
        break;
      case OP_MULTIPLY:
        BINARY_OP(*);
        break;
      case OP_DIVIDE:
        BINARY_OP(/);
        break;
      case OP_NEGATE:
        push(-pop());
        break;
      case OP_RETURN: {
        printValue(pop());
        printf("\n");
        return INTERPRET_OK;
      }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef READ_CONSTANT_LONG
#undef BINARY_OP
}

InterpretResult interpret(const char* source) {
  Chunk chunk;
  initChunk(&chunk);

  if (!compile(source, &chunk)) {
    freeChunk(&chunk);
    return INTERPRET_COMPILE_ERROR;
  }

  vm.chunk = &chunk;
  vm.ip = vm.chunk->code;

  InterpretResult result = run();

  freeChunk(&chunk);
  return result;
}
