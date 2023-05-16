/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 *
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE for details for
 * more details about how you can use it, you have freedom
 * to distribute and use this file in your project. However,
 * you will have to state changes you made and include the
 * orginal author of this file.
 *
 * ir.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "ir.h"
#include "../memory/memory.h"

void emptyIR(IR *ir)
{
    Position empty = {0,0};
    ir->count = 0;
    ir->volume = 0;
    ir->code = NULL;
    ir->pos = empty;
}

void initIR(IR *ir)
{
    emptyIR(ir);
    initDataCollection(&ir->coll);
}

void createIR(IR *ir, uint8_t code, Position where)
{
    int currentVolume = ir->volume;
    if (currentVolume <= ir->volume)
    {
        ir->volume = allocVolume(currentVolume);
        ir->code = increaseMemory(uint8_t, ir->code, ir->volume);
    }

    ir->code[ir->count] = code;
    ir->pos = where;
    ir->count++;
}

/**
 * Free the memory the IR occupies back to the computer
 */
void releaseIR(IR *ir)
{
    freeMemory(uint8_t, ir->code);
    releaseDataCollection(&ir->coll);
    emptyIR(ir);
}

int addData(IR *ir, Data data)
{

    createDataCollection(&ir->coll, data);
    return ir->coll.count - 1;
}
