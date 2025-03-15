#include "../include/chunk.h"
#include "../include/common.h"
#include "../include/debug.h"
#include <stdio.h>

int main(void /*int argsc, char **argsv*/) {
  Chunk chunk;

  initChunk(&chunk);

  int constant = addConstant(&chunk, 2.1);

  writeChunk(&chunk, OP_CONSTANT);
  writeChunk(&chunk, constant);
  writeChunk(&chunk, OP_RETURN);

  disassembleChunk(&chunk, "test chunk");

  freeChunk(&chunk);

  return 0;
}
