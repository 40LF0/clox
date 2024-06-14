// compiler.c
// Created by Seungyeon Chung on 2024.06.12.
// A compiler is a component that generate bytecode chunk from tokens.

#include "compiler.h"

#include <stdio.h>

#include "common.h"
#include "scanner.h"

void compile(const char *source) {
  initScanner(source);
  int line = -1;
  for (;;) {
    Token token = scanToken();
    if (token.line != line) {
      printf("%4d ", token.line);
      line = token.line;
    } else {
      printf("   | ");
    }
    printf("%2d '%.*s'\n", token.type, token.length, token.start);

    if (token.type == TOKEN_EOF) break;
  }
}
