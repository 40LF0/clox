// compiler.c
// Created by Seungyeon Chung on 2024.06.12.
// A compiler is a component that generate bytecode chunk from tokens.

#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char *source) {
  initScanner(source);
}
