#include "../include/vm.h"
#include "../include/common.h"
#include "../include/compiler.h"
#include "../include/debug.h"
#include <stdio.h>

VM vm;

static void resetStack() { vm.stackTop = vm.stack; }

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                                                          \
  do {                                                                         \
    double rhs = pop();                                                        \
    double lhs = pop();                                                        \
    push(lhs op rhs);                                                          \
  } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[");
      printValue(*slot);
      printf("]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      push(constant);
      break;
    }
    case OP_ADD:
      BINARY_OP(+);
      break;
    case OP_SUB:
      BINARY_OP(-);
      break;
    case OP_MUL:
      BINARY_OP(*);
      break;
    case OP_DIV:
      BINARY_OP(/);
      break;
    case OP_NEGATE: {
      push(-pop());
      break;
    }
    case OP_RETURN: {
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;
    }
    }
  }

#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

void initVM() { resetStack(); }

void freeVM() {}

InterpretResult interpret(const char *source) {
  Chunk chunk;

  initChunk(&chunk);

  if (!compile(source, &chunk)) {
    freeChunk(&chunk);
    return INTERPRET_COMPILE_ERROR;
  }

  vm.chunk = &chunk;
  vm.ip = chunk.code;

  InterpretResult result = run();

  freeChunk(&chunk);

  return result;
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() { return *(--vm.stackTop); }
