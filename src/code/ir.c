#include <stdlib.h>
#include <stdio.h>
#include "ir.h"
#include "../security/alloc.h"

void emptyIR(IR* ir) {
    Position emptypos;
    emptypos.row = 0;
    emptypos.col = 0;

    ir->counter = 0;
    ir->volume = 0;
    ir->code = NULL;
    ir->pos = emptypos;
    initDataValuesList(&ir->list);
}

void initIR(IR* ir) {
    emptyIR(ir);
}

int addDataValueToList(IR* ir, DataValue val) {
    writeDataValuesList(&ir->list, val);
    return ir->list.counter - 1;
}

static void freePosition(Position* pos, int v) {
    pos->row = 0; 
    pos->col = 0; 
    FREE_SPACE(Position, pos, v);
}

void freeIR(IR* ir) {
    FREE_SPACE(uint8_t, ir->code, ir->volume);
    freeDataValuesList(&ir->list);
    emptyIR(ir);
}

void writeIR(IR* ir, uint8_t stuff, Position pos) {
    if (ir->volume < ir->counter + 1) {
        int vol = ir->volume;
        ir->volume = MORE_VOLUME(vol);
        ir->code = MORE_SPACE(uint8_t, ir->code, vol, ir->volume);
    }
    ir->code[ir->counter] = stuff;
    ir->pos = pos;
    ir->counter++;
}

void defineConstant(IR* ir, DataValue val, Position pos) {
    int maxidx = addDataValueToList(ir, val);
    if (maxidx < 256) {
        writeIR(ir, INS_DEFCONST, pos);
        writeIR(ir, (uint8_t)maxidx, pos);
        return;
    }
    writeIR(ir,INS_DEFCONST_LARGE, pos);
    writeIR(ir, (uint8_t)(maxidx & 0xff), pos);
    writeIR(ir, (uint8_t)((maxidx >> 8) & 0xff), pos);
    writeIR(ir, (uint8_t)((maxidx >> 16) & 0xff), pos);
}
