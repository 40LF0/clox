// scanner_test.c
// Created by Seungyeon Chung on 2024.06.28.
//
// Test file for scanner module.

#include "scanner.c"

#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_Scanner_Init(void) {
  const char* source = "var x = 10;";
  initScanner(source);
  TEST_ASSERT_NOT_NULL(scanner.start);
  TEST_ASSERT_EQUAL(scanner.start, source);
  TEST_ASSERT_EQUAL(scanner.current, source);
  TEST_ASSERT_EQUAL(scanner.line, 1);
}

void test_Scanner_AllTokens(void) {
  const char* source =
      "(){},.-+;/* ! != = == > >= < <= "
      "and class else false for fun if nil or print return super this true var "
      "while "
      "\"string\" 1234";
  initScanner(source);

  Token token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_LEFT_PAREN, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_RIGHT_PAREN, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_LEFT_BRACE, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_RIGHT_BRACE, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_COMMA, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_DOT, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_MINUS, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_PLUS, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_SEMICOLON, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_SLASH, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_STAR, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_BANG, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_BANG_EQUAL, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_EQUAL, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_EQUAL_EQUAL, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_GREATER, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_GREATER_EQUAL, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_LESS, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_LESS_EQUAL, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_AND, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_CLASS, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_ELSE, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_FALSE, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_FOR, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_FUN, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_IF, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_NIL, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_OR, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_PRINT, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_RETURN, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_SUPER, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_THIS, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_TRUE, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_VAR, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_WHILE, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_STRING, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_NUMBER, token.type);
  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_EOF, token.type);
}

void test_Scanner_Tokens(void) {
  const char* source = "var x = 10; print(x);";
  initScanner(source);

  Token token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_VAR, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER, token.type);
  TEST_ASSERT_EQUAL_STRING_LEN("x", token.start, token.length);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_EQUAL, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_NUMBER, token.type);
  TEST_ASSERT_EQUAL_STRING_LEN("10", token.start, token.length);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_SEMICOLON, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_PRINT, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_LEFT_PAREN, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER, token.type);
  TEST_ASSERT_EQUAL_STRING_LEN("x", token.start, token.length);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_RIGHT_PAREN, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_SEMICOLON, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_EOF, token.type);
}

void test_Scanner_String(void) {
  const char* source = "\"Hello, world!\"";
  initScanner(source);

  Token token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_STRING, token.type);
  TEST_ASSERT_EQUAL_STRING_LEN(
      "Hello, world!", token.start + 1,
      token.length - 2);  // Exclude the surrounding quotes
}

void test_Scanner_Comments(void) {
  const char* source = "var x = 10; // This is a comment\nprint(x);";
  initScanner(source);

  Token token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_VAR, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER, token.type);
  TEST_ASSERT_EQUAL_STRING_LEN("x", token.start, token.length);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_EQUAL, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_NUMBER, token.type);
  TEST_ASSERT_EQUAL_STRING_LEN("10", token.start, token.length);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_SEMICOLON, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_PRINT, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_LEFT_PAREN, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER, token.type);
  TEST_ASSERT_EQUAL_STRING_LEN("x", token.start, token.length);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_RIGHT_PAREN, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_SEMICOLON, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_EOF, token.type);
}

void test_Scanner_Keywords(void) {
  const char* source = "class for if while";
  initScanner(source);

  Token token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_CLASS, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_FOR, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_IF, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_WHILE, token.type);
}
void test_Scanner_Operators(void) {
  const char* source = "!= == <= >= && ||";
  initScanner(source);

  Token token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_BANG_EQUAL, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_EQUAL_EQUAL, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_LESS_EQUAL, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_GREATER_EQUAL, token.type);

  token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_ERROR,
                    token.type);  // Note: && and || are not defined in the
                                  // enum, should return TOKEN_ERROR
}

void test_Scanner_UnterminatedString(void) {
  const char* source = "\"Hello, world";
  initScanner(source);

  Token token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_ERROR, token.type);
  TEST_ASSERT_EQUAL_STRING("Unterminated string.", token.start);
}

void test_Scanner_InvalidCharacter(void) {
  const char* source = "@";
  initScanner(source);

  Token token = scanToken();
  TEST_ASSERT_EQUAL(TOKEN_ERROR, token.type);
  TEST_ASSERT_EQUAL_STRING("Unexpected character.", token.start);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_Scanner_Init);
  RUN_TEST(test_Scanner_AllTokens);
  RUN_TEST(test_Scanner_Tokens);
  RUN_TEST(test_Scanner_String);
  RUN_TEST(test_Scanner_Comments);
  RUN_TEST(test_Scanner_Keywords);
  RUN_TEST(test_Scanner_Operators);
  RUN_TEST(test_Scanner_UnterminatedString);
  RUN_TEST(test_Scanner_InvalidCharacter);
  return UNITY_END();
}