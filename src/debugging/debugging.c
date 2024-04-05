#include <stdio.h>
#include "debugging.h"
#include "../types/types.h"

void showIR(IR* ir, const char* testname) {
    #ifdef READY
       return;
    #endif
    #ifndef COMPILE_DEBUGGING
        return;
    #endif
    printf("DEBUGGING: %s\n\n",testname);
    for (int idx = 0; idx < ir->counter;) {
        idx = showInstruction(ir, idx);
    }
    printf("\nTOTAL:\trows:%03d, cols:%03d\n", ir->pos.row,ir->pos.col);
}

static int displayUnknownInstruction(int inscode, int idx) {
    printf("Unkown instruction %d\n", inscode);
    return idx + 1;
}

static int displayInstruction(const char* ins, int idx) {
    printf("%s\n", ins);
    return idx + 1;
}

static int displayOneOperandInstruction(const char* ins, IR* ir, int idx) {
    uint8_t operand = ir->code[idx + 1];
    printf("%-12s\t%6d (", ins, operand);
    printStuff(ir->list.data[operand]);
    printf(")\n");
    return idx + 2;
}

static int displayLargeOneOperandInstruction(const char* ins, IR* ir, int idx) {
    uint32_t operand = ir->code[idx + 1] | (ir->code[idx + 2] << 8) | (ir->code[idx + 3] << 16);
    printf("%-12s\t%6d (", ins, operand);
    printStuff(ir->list.data[operand]);
    printf(")\n");
    return idx + 4;
}

// main instruction function
int showInstruction(IR* ir, int idx) {
    printf("%06d\t", idx);
    uint8_t inst = ir->code[idx];
    switch (inst) {
        default:
            return displayUnknownInstruction(inst, idx);

        case INS_RETURN:
            return displayInstruction("INS_RET", idx);
        case INS_NEGATE:
            return displayInstruction("INS_NEGATE", idx);
        case INS_ADD:
            return displayInstruction("INS_ADD", idx);
        case INS_SUB:
            return displayInstruction("INS_SUB", idx);
        case INS_MUL:
            return displayInstruction("INS_MUL", idx);
        case INS_DIV:
            return displayInstruction("INS_DIV", idx);
        case INS_DEFCONST:
            return displayOneOperandInstruction("INS_DEFCONST", ir, idx);
        case INS_DEFCONST_LARGE:
            return displayLargeOneOperandInstruction("INS_DEFCONST_LARGE", ir, idx);
    }
}

void printStuff(DataValue val) {
    printf("%g", val);
}
