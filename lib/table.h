// table.h
// Created by Seungyeon Chung on 2024.07.02.
//
// This module defines and implements a hash table.

#ifndef CLOX_TABLE_H
#define CLOX_TABLE_H

#include "common.h"
#include "value.h"

typedef struct {
  ObjString* key;
  Value value;
} Entry;

typedef struct {
  int count;
  int capacity;
  Entry* entries;
} Table;

void initTable(Table* table);
void freeTable(Table* table);
bool tableSet(Table* table, ObjString* key, Value value);
void tableAddAll(Table* from, Table* to);

#endif  // CLOX_TABLE_H
