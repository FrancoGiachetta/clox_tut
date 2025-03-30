#ifndef clox_compiler_h
#define clox_compiler_h

#include "../include/scanner.h"
#include "vm.h"
#include <stdio.h>

typedef struct {
  bool hadError;
  bool panicMode;
  Token previous;
  Token current;
} Parser;

bool compile(const char *source, Chunk *chunk);

#endif
