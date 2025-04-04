#ifndef clox_scanner_h
#define clox_scanner_h

#include <stdio.h>
#include <string.h>

#include "../include/common.h"

typedef struct {
  const char *start;
  const char *current;
  int line;
} Scanner;

typedef enum {
  // Single character tokens
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_BRACE,
  TOKEN_RIGHT_BRACE,
  TOKEN_COMMA,
  TOKEN_DOT,
  TOKEN_MINUS,
  TOKEN_PLUS,
  TOKEN_SEMICOLON,
  TOKEN_SLASH,
  TOKEN_STAR,
  // One or two character tokens
  TOKEN_BANG,
  TOKEN_BANG_EQUAL,
  TOKEN_EQUAL,
  TOKEN_EQUAL_EQUAL,
  TOKEN_GREATER,
  TOKEN_GREATER_EQUAL,
  TOKEN_LESS,
  TOKEN_LESS_EQUAL,
  // Literals
  TOKEN_IDENTIFIER,
  TOKEN_STRING,
  TOKEN_NUMBER,
  // Keywords
  TOKEN_AND,
  TOKEN_OR,
  TOKEN_IF,
  TOKEN_ELSE,
  TOKEN_TRUE,
  TOKEN_FALSE,
  TOKEN_WHILE,
  TOKEN_FOR,
  TOKEN_FUN,
  TOKEN_RETURN,
  TOKEN_CLASS,
  TOKEN_THIS,
  TOKEN_SUPER,
  TOKEN_NIL,
  TOKEN_VAR,
  TOKEN_PRINT,

  TOKEN_ERROR,
  TOKEN_EOF
} TokenType;

typedef struct {
  TokenType type;
  const char *start;
  int length;
  int line;
} Token;

void initScanner(const char *source);
Token scanToken();

#endif
