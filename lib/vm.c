// VM.c
// Created by Seungyeon Chung on 2024.06.09.
//
// A virtual machine is a component that interprets and executes chunks of code.

#include "vm.h"

#include <stdio.h>

#include "common.h"
#include "debug.h"

VM vm;

void initVM() {}

void freeVM() {}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define READ_CONSTANT_LONG() \
  (vm.chunk->constants       \
       .values[READ_BYTE() << 16 | READ_BYTE() << 8 | READ_BYTE()])

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
      Value constant;
      case OP_CONSTANT:
        constant = READ_CONSTANT();
        printValue(constant);
        printf("\n");
        break;
      case OP_CONSTANT_LONG:
        constant = READ_CONSTANT_LONG();
        printValue(constant);
        printf("\n");
        break;
      case OP_RETURN:
        return INTERPRET_OK;
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef READ_CONSTANT_LONG
}

InterpretResult interpret(Chunk *chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}
