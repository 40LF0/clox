// compiler.c
// Created by Seungyeon Chung on 2024.06.12.
// A compiler is a component that generate bytecode chunk from tokens.

#include "compiler.h"

#include <stdio.h>

#include "common.h"
#include "scanner.h"

static void advance() {}

static void expression() {}

static void consume(TokenType type, const char* message) {}

bool compile(const char* source, Chunk* chunk) {
  initScanner(source);
  advance();
  expression();
  consume(TOKEN_EOF, "Expect end of expression.");
  return true;
}
