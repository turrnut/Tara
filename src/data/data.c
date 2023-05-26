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

/**
 * This function takes in a DataCollection pointer as an
 * argument, then set all the properties empty.
 * 
*/
void emptyDataCollection(DataCollection *coll)
{
    coll->elements = NULL;
    coll->volume = 0;
    coll->count = 0;
}

/**
 * This function takes in a DataCollection pointer as an
 * argument and then initialize an empty DataCollection
 * instance.
*/
void initDataCollection(DataCollection *coll)
{
    emptyDataCollection(coll); // Empty collection
}

/**
 * Add a new Data instance to the DataCollection
 * pointer. The first argument is the DataCollection
 * pointer and the second argument is the value you want
 * to add.
*/
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

/**
 * Empty the DataCollection. Takes in a DataCollection
 * pointer as the argument.
*/
void releaseDataCollection(DataCollection *coll)
{
    freeMemory(Data, coll->elements); // Free all memory
    emptyDataCollection(coll); // Empty the DataCollection
}

/**
 * Print the data.
*/
void printData(Data d)
{
    printf("%g", d);
}
