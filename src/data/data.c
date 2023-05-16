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
 * data.c
 *
 */
#include "data.h"
#include "../memory/memory.h"

void emptyDataCollection(DataCollection *coll)
{
    coll->elements = NULL;
    coll->volume = 0;
    coll->count = 0;
}
void initDataCollection(DataCollection *coll)
{
    emptyDataCollection(coll);
}
void createDataCollection(DataCollection *coll, Data value)
{

    if (coll->volume <= coll->count)
    {
        int currentVolume = coll->volume;
        coll->volume = allocVolume(currentVolume);
        coll->elements = increaseMemory(Data, coll->elements, coll->volume);
    }

    coll->elements[coll->count] = value;
    coll->count++;
}
void releaseDataCollection(DataCollection *coll)
{

    freeMemory(Data, coll->elements);
    emptyDataCollection(coll);
}

void printData(Data d)
{
    printf("%g", d);
}
