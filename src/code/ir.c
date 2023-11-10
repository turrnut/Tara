#include <stdlib.h>
#include <stdio.h>
#include "ir.h"
#include "../security/alloc.h"

void emptyIR(IR* ir) {
    Position default_position = {
        row :0,
        col :0
    };
    ir->counter = 0;
    ir->volume = 0;
    ir->code = NULL;
    ir->pos = default_position;
    initDataValuesList(&ir->list);
}

void initIR(IR* ir) {
    emptyIR(ir);
}

int addDataValue(IR* ir, DataValue val) {
    writeDataValuesList(&ir->list, val);
    return ir->list.counter - 1;
}

void freeIR(IR* ir) {
    FREE_SPACE(uint8_t, ir->code, ir->volume);
    freeDataValuesList(&ir->list);
    emptyIR(ir);
}

void writeIR(IR* ir, uint8_t stuff) {
    if (ir->volume < ir->counter + 1) {
        int vol = ir->volume;
        ir->volume = MORE_VOLUME(vol);
        ir->code = MORE_SPACE(uint8_t, ir->code, vol, ir->volume);
    }
    ir->code[ir->counter] = stuff;
    ir->counter++;
}
