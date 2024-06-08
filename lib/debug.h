// debug.h
// Created by Seungyeon Chung on 2024.06.08.
//
// This module provides functionality to disassemble chunks of bytecode.
// It helps in debugging by printing out the instructions in a human-readable format.

#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "chuck.h"

void disassembleChunk(Chunk* chunk, const char * name);
int disassembleInstruction(Chunk* chunk, int offset);

#ifdef __cplusplus
}
#endif

#endif // CLOX_DEBUG_H
