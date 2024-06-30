// object.h
// Created by Seungyeon Chung on 2024.06.29.
//
// This module defines a object, which represets Value expect number and
// boolean.

#ifndef OBJECT_H
#define OBJECT_H

#include "common.h"
#include "value.h"

#define OBJ_TPYE(value) (AS_OBJ(value)->type)

#define IS_STRING(value) isObjType(value, OBJ_STRING)

#define AS_STRING(value) ((ObjString*)AS_OBJ((value)))
#define AS_CSTRING(value) (((ObjString*)AS_OBJ((value)))->chars)

typedef enum {
  OBJ_STRING,
} ObjType;

struct Obj {
  ObjType type;
  struct Obj* next;
};

struct ObjString {
  Obj obj;
  int length;
  char* chars;
};

ObjString* takeString(char* chars, int length);
ObjString* copyString(const char* chars, int length);
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif  // OBJECT_H
