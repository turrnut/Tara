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
 * Implementation of data.h , go there to see more documentation.
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
    emptyDataCollection(coll); // Empty collection
}

void createDataCollection(DataCollection *coll, Data value)
{

    if (coll->volume <= coll->count) // Check to see if there is enough space
    {
        // If not, allocate more
        int currentVolume = coll->volume; // Get the size of the volume the DataCollection currently has
        coll->volume = allocVolume(currentVolume); // Determine how much volume should be used
        coll->elements = increaseMemory(Data, coll->elements, coll->volume); // Allocate more memory usage
    }

    coll->elements[coll->count] = value; // Add the element to the DataCollection
    coll->count++; // Increment the count
}


void releaseDataCollection(DataCollection *coll)
{
    freeMemory(Data, coll->elements); // Free all memory
    emptyDataCollection(coll); // Empty the DataCollection
}

void printData(Data d)
{
    printf("%g", d);
}
