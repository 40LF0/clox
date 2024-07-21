// main.c
// Created by Seungyeon Chung on 2024.06.07.
//
// Entry point for the interpreter. This file contains the main function.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

static void repl() {
  for (;;) {
    char line[1024];
    printf(">");

    if (fgets(line, sizeof(line), stdin) == 0) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

static char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");

  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\". \n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\". \n", path);
    exit(74);
  }

  size_t byteRead = fread(buffer, sizeof(char), fileSize, file);
  if (byteRead < fileSize) {
    fprintf(stderr, "Could not read file \"%s\". \n", path);
    exit(74);
  }

  buffer[byteRead] = '\0';

  fclose(file);
  return buffer;
}

static void runFile(const char* path) {
  char* source = readFile(path);
  InterpretResult result = interpret(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR) exit(65);
  if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, const char* argv[]) {
  initVM();

  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
  }

  freeVM();
  return 0;
}