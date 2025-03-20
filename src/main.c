#include "../include/chunk.h"
#include "../include/common.h"
#include "../include/debug.h"
#include "../include/vm.h"
#include <stdio.h>

int main(void /*int argsc, char **argsv*/) {
  initVM();
  Chunk chunk;

  initChunk(&chunk);

  int constant = addConstant(&chunk, 2.1);

  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  writeChunk(&chunk, OP_RETURN, 123);

  disassembleChunk(&chunk, "test chunk");

  interpret(&chunk);

  freeVM();
  freeChunk(&chunk);

  return 0;
}
