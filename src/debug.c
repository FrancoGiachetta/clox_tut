#include "../include/debug.h"
#include "../include/value.h"
#include <stdint.h>
#include <stdio.h>

static int simpleInstruction(const char *name, int offset) {
  printf("%s\n", name);

  return offset + 1;
}

static int constantInstruction(const char *name, Chunk *chunk, int offset) {
  uint8_t constant_index = chunk->code[offset + 1];

  printf("%s %d '", name, constant_index);
  printValue(chunk->constants.values[constant_index]);
  printf("'\n");

  return offset + 2;
}

void disassembleChunk(Chunk *chunk, const char *name) {
  printf("=== %s ===\n", name);

  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

int disassembleInstruction(Chunk *chunk, int offset) {
  printf("%04d ", offset);

  uint8_t instruction = chunk->code[offset];

  switch (instruction) {
  case OP_RETURN:
    return simpleInstruction("OP_RETURN", offset);
  case OP_CONSTANT:
    return constantInstruction("OP_CONSTANT", chunk, offset);
  default:
    printf("Unknown opcode %d\n", instruction);
    return offset + 1;
  }
}
