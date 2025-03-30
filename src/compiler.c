#include "../include/compiler.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Parser parser;
Chunk *compilingChunk;

static Chunk *currentChunk() { return compilingChunk; }

static void errorAt(Token *token, const char *message) {
  if (parser.panicMode)
    return;

  parser.panicMode = true;
  fprintf(stderr, "[line %d] Error", token->line);

  if (token->type == TOKEN_EOF) {
    fprintf(stderr, " at end");
  } else if (token->type == TOKEN_ERROR) {
  } else {
    fprintf(stderr, " at '%.*s'", token->line, token->start);
  }

  fprintf(stderr, ": %s\n", message);
  parser.hadError = true;
}

static void errorAtCurrent(const char *message) {
  errorAt(&parser.current, message);
}

static void error(const char *message) { errorAt(&parser.previous, message); }

static void advance() {
  parser.previous = parser.current;

  for (;;) {
    parser.current = scanToken();

    if (parser.current.type != TOKEN_ERROR)
      break;

    errorAtCurrent(parser.current.start);
  }
}

static void consume(TokenType type, const char *message) {
  if (parser.current.type == type) {
    advance();
    return;
  }

  errorAtCurrent(message);
}

static void emiteByte(uint8_t byte) {
  writeChunk(currentChunk(), byte, parser.previous.line);
}

static void emiteBytes(uint8_t byte1, uint8_t byte2) {
  emiteByte(byte1);
  emiteByte(byte2);
}

static void emitReturn() { emiteByte(OP_RETURN); }

static uint8_t makeConstant(Value value) {
  int constant = addConstant(currentChunk(), value);

  if (constant > UINT8_MAX) {
    error("Too many constants in one chunk.");
    return 0;
  }

  return (uint8_t)constant;
}

static void emitConstant(Value value) {
  emiteBytes(OP_CONSTANT, makeConstant(value));
}

static void endCompiler() { emitReturn(); }

static void expression() {
  //
}

static void grouping() {
  expression();
  consume(TOKEN_RIGHT_PAREN, "Expected ')' after expression.");
}

static void number() {
  double value = strtod(parser.previous.start, NULL);
  emitConstant(value);
}

bool compile(const char *source, Chunk *chunk) {
  initScanner(source);
  compilingChunk = chunk;

  parser.hadError = false;
  parser.panicMode = false;

  advance();
  expression();
  consume(TOKEN_EOF, "Expect end of expression.");

  endCompiler();

  return !parser.hadError;
}
