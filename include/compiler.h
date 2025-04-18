#ifndef clox_compiler_h
#define clox_compiler_h

#include "../include/scanner.h"
#include "vm.h"
#include <stdio.h>

typedef void (*ParseFn)();

typedef struct
{
    bool hadError;
    bool panicMode;
    Token previous;
    Token current;
} Parser;

typedef enum
{
    PREC_NONE,
    PREC_ASSIGN, // =
    PREC_OR,     // or
    PREC_AND,    // and
    PREC_EQ,     // == !=
    PREC_COMP,   // < > <= >=
    PREC_TERM,   // + -
    PREC_FACTOR, // * /
    PREC_UNARY,  // ! -
    PREC_CALL,   // . ()
    PREC_PRIMARY,
} Precedence;

typedef struct
{
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
} ParseRule;

bool compile(const char *source, Chunk *chunk);

#endif
