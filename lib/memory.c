// memory.c
// Created by Seungyeon Chung on 2024.06.07.
//
// This module is responsible for low-level memory operations.

#include "memory.h"

#include <stdlib.h>

#include "object.h"
#include "vm.h"

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void *result = realloc(pointer, newSize);
  if (result == NULL) exit(1);
  return result;
}

static void freeObject(Obj *object) {
  switch (object->type) {
    case OBJ_STRING: {
      ObjString *string = (ObjString *)object;
      FREE_ARRAY(char, string->chars, string->length + 1);
      FREE(ObjString, object);
      break;
    }
  }
}

void *freeObjects() {
  Obj *object = vm.objects;
  while (object != NULL) {
    Obj *next = object->next;
    freeObject(object);
    object = next;
  }
}
