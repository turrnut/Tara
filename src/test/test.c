/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 *
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE for more details about
 * how you can use it, you have freedom to distribute and
 * use this code in your project. However, you will have to
 * state changes you made and include the orginal author of
 * this code.
 *
 * test.c
 *
 */
#include "test.h"
#include <time.h>
#include "../types/types.h"

void printName(const char* name) {
    printf("========================\nIR Test\t|\tTest Name: \"%s\"\n========================\n\n", name);
}

void showIR(IR *ir, const char *name)
{
    printName(name);
    for (int offset = 0; offset < ir->count;)
    {
        offset = showIns(ir, offset);
    }
}

void ins(const char *name, int offset)
{
    printf("%s\t\t\t", name);
}

void insD(const char *name, IR *ir,
          int offset)
{
    uint8_t data = ir->code[offset + 1];
    printf("%-16s %4d \'", name, data);
    printData(ir->coll.elements[data]);
    printf("\'\t");
}

void showPosition(Position pos)
{
    printf("Row:%4d\t", pos.row);
    printf("Col:%4d\t", pos.col);
    printf("\n");
}

int showIns(IR *ir, int i) {
    printf("%08d ", i);

    uint8_t instruction = ir->code[i];
    switch (instruction)
    {
    case INS_DATA:
        insD("INS_DATA", ir, i);
        showPosition(ir->pos);
        return 2 + i;

    case INS_RETURN:
        ins("INS_RETURN", i);
        showPosition(ir->pos);
        return 1 + i;
    case INS_NEGATIVE:
        ins("INS_NEGATIVE", i);
        showPosition(ir->pos);
        
        return 1 + i;
    case INS_ADD:
        ins("INS_ADD", i);showPosition(ir->pos);return 1 + i;
    case INS_SUB:
        ins("INS_SUB", i);showPosition(ir->pos);return 1 + i;
    case INS_MUL:
        ins("INS_MUL", i);showPosition(ir->pos);return 1 + i;
    case INS_DIV:
        ins("INS_DIV", i);showPosition(ir->pos);return 1 + i;
    case INS_NOT:ins("INS_NOT", i);showPosition(ir->pos);return 1+i;
    case INS_DATA_NULL:
        ins("INS_DATA_NULL", i);showPosition(ir->pos);return 1 + i;
    case INS_DATA_TRUE:
        ins("INS_DATA_TRUE", i);showPosition(ir->pos);return 1 + i;
    case INS_DATA_FALSE:
        ins("INS_DATA_FALSE", i);showPosition(ir->pos);return 1 + i;
    case INS_EQUAL:ins("INS_EQUAL", i);showPosition(ir->pos);return 1+i;
    case INS_NOT_EQUAL:ins("INS_NOT_EQUAL", i);showPosition(ir->pos);return 1+i;
    case INS_GREATER_THAN:ins("INS_GREATER_THAN", i);showPosition(ir->pos);return 1+i;
    case INS_GREATER_THAN_OR_EQUAL_TO:ins("INS_GREATER_THAN_OR_EQUAL_TO", i);showPosition(ir->pos);return 1+i;
    case INS_LESS_THAN:ins("INS_LESS_THAN", i);showPosition(ir->pos);return 1+i;
    case INS_LESS_THAN_OR_EQUAL_TO:ins("INS_LESS_THAN_OR_EQUAL_TO", i);showPosition(ir->pos);return 1+i;
    default:
        printf("Unknown instruction code %d\n", instruction);
    }
}
