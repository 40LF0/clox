// compiler.h
// Created by Seungyeon Chung on 2024.06.12.
//
// The compiler is a component that generates bytecode chunks from tokens.

#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "object.h"
#include "vm.h"

ObjFunction* compile(const char* source);
void markCompilerRoots();

#endif  // CLOX_COMPILER_H
