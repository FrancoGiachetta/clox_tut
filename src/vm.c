#include "../include/common.h"
#include "../include/compiler.h"
#include "../include/debug.h"
#include "../include/vm.h"
#include <stdarg.h>
#include <stdio.h>

VM vm;

static void resetStack()
{
    vm.stackTop = vm.stack;
}

static void runtimeError(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fputs("\n", stderr);
    size_t intruction = vm.ip - vm.chunk->code - 1;
    int line = vm.chunk->lines[intruction];
    fprintf(stderr, "[line %d] in script\n", line);
    resetStack();
}

void initVM()
{
    resetStack();
}

void freeVM()
{
}

void push(Value value)
{
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop()
{
    return *(--vm.stackTop);
}

static Value peek(int distance)
{
    return vm.stackTop[-1 - distance];
}

static InterpretResult run()
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(valueType, op)                                                                                       \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1)))                                                                \
        {                                                                                                              \
            runtimeError("Operands must be numbers");                                                                  \
            return INTERPRET_RUNTIME_ERROR;                                                                            \
        }                                                                                                              \
        double rhs = AS_NUMBER(pop());                                                                                 \
        double lhs = AS_NUMBER(pop());                                                                                 \
        push(valueType(lhs op rhs));                                                                                   \
    } while (false)

    for (;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value *slot = vm.stack; slot < vm.stackTop; slot++)
        {
            printf("[");
            printValue(*slot);
            printf("]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;

        switch (instruction = READ_BYTE())
        {
        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            push(constant);
            break;
        }
        case OP_ADD:
            BINARY_OP(NUMBER_VAL, +);
            break;
        case OP_SUB:
            BINARY_OP(NUMBER_VAL, -);
            break;
        case OP_MUL:
            BINARY_OP(NUMBER_VAL, *);
            break;
        case OP_DIV:
            BINARY_OP(NUMBER_VAL, /);
            break;
        case OP_NEGATE: {
            if (!IS_BOOL(peek(0)))
            {
                runtimeError("Operand must be a number");
                return INTERPRET_RUNTIME_ERROR;
            }
            push(NUMBER_VAL(-AS_NUMBER(pop())));
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

InterpretResult interpret(const char *source)
{
    Chunk chunk;

    initChunk(&chunk);

    if (!compile(source, &chunk))
    {
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.chunk = &chunk;
    vm.ip = chunk.code;

    InterpretResult result = run();

    freeChunk(&chunk);

    return result;
}
