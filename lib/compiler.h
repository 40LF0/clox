// compiler.h
// Created by Seungyeon Chung on 2024.06.12.
// A compiler is a component that generate bytecode chunk from tokens.

#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "object.h"
#include "vm.h"

bool compile(const char* source, Chunk* chunk);

#endif  // CLOX_COMPILER_H
