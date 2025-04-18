#include "../include/debug.h"
#include "../include/value.h"
#include <stdint.h>
#include <stdio.h>

static int simpleInstruction(const char *name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char *name, Chunk *chunk, int offset)
{
    uint8_t constant_index = chunk->code[offset + 1];

    printf("%-16s %4d '", name, constant_index);
    printValue(chunk->constants.values[constant_index]);
    printf("'\n");

    return offset + 2;
}

void disassembleChunk(Chunk *chunk, const char *name)
{
    printf("=== %s ===\n", name);

    for (int offset = 0; offset < chunk->count;)
    {
        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(Chunk *chunk, int offset)
{
    printf("%04d ", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
        printf("   | ");
    else
        printf("%4d ", chunk->lines[chunk->count - 1]);

    uint8_t instruction = chunk->code[offset];

    switch (instruction)
    {
    case OP_NEGATE:
        return simpleInstruction("OP_NEGATE", offset);
    case OP_NOT:
        return simpleInstruction("OP_NOT", offset);
    case OP_CONSTANT:
        return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_NIL:
        return simpleInstruction("OP_NIL", offset);
    case OP_TRUE:
        return simpleInstruction("OP_TRUE", offset);
    case OP_FALSE:
        return simpleInstruction("OP_FALSE", offset);
    case OP_EQ:
        return simpleInstruction("OP_EQ", offset);
    case OP_GREATER:
        return simpleInstruction("OP_GREATER", offset);
    case OP_LESS:
        return simpleInstruction("OP_LESS", offset);
    case OP_ADD:
        return simpleInstruction("OP_ADD", offset);
    case OP_SUB:
        return simpleInstruction("OP_SUB", offset);
    case OP_MUL:
        return simpleInstruction("OP_MUL", offset);
    case OP_DIV:
        return simpleInstruction("OP_DIV", offset);
    case OP_RETURN:
        return simpleInstruction("OP_RETURN", offset);
    default:
        printf("Unknown opcode %d\n", instruction);
        return offset + 1;
    }
}
