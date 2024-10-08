// scanner.h
// Created by Seungyeon Chung on 2024.06.14.
//
// The scanner is a component that parses source code and generates tokens.

#ifndef CLOX_SCANNER_H
#define CLOX_SCANNER_H

typedef enum {
  // 1-character  token
  TOKEN_LEFT_PAREN,TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_BRACE,TOKEN_RIGHT_BRACE,
  TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
  TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR, TOKEN_COLON,
  // 1-character or 2-character token
  TOKEN_BANG, TOKEN_BANG_EQUAL,
  TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
  TOKEN_GREATER, TOKEN_GREATER_EQUAL,
  TOKEN_LESS, TOKEN_LESS_EQUAL,
  // literal
  TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,
  // keyword
  TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
  TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NIL, TOKEN_OR,
  TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
  TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE, TOKEN_SWITCH, TOKEN_CASE, TOKEN_DEFAULT,

  TOKEN_ERROR, TOKEN_EOF, TOKEN_SYNTHETIC

} TokenType;

typedef struct {
  TokenType type;
  const char* start;
  int length;
  int line;
} Token;

void initScanner(const char* source);
Token scanToken();

#endif  // CLOX_SCANNER_H
