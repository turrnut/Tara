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
 * data.h
 * This header file provide declarations for the Data type.
 * The Data type was created in order to store information
 * during runtime. For example the stack memory uses a
 * pointer of the type Data to store data in the program.
 */
#ifndef data_header
#define data_header

#include "../base/base.h"

typedef double Data;

/**
 * The DataCollection type definition
 * 
*/
typedef struct
{
    int volume;
    int count;
    Data *elements;
} DataCollection;

/**
 * This function takes in a DataCollection pointer as an
 * argument, then set all the properties empty.
 * 
*/
void emptyDataCollection(DataCollection *coll);

/**
 * This function takes in a DataCollection pointer as an
 * argument and then initialize an empty DataCollection
 * instance.
*/
void initDataCollection(DataCollection *coll);

/**
 * Add a new Data instance to the DataCollection
 * pointer. The first argument is the DataCollection
 * pointer and the second argument is the value you want
 * to add.
*/
void createDataCollection(DataCollection *coll, Data value);

/**
 * Free the DataCollection back to the memory. Takes in a
 * DataCollection pointer as the argument.
*/
void releaseDataCollection(DataCollection *coll);

/**
 * Print the data.
*/
void printData(Data d);

#endif
