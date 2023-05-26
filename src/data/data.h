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

typedef struct
{
    int volume;
    int count;
    Data *elements;
} DataCollection;

void emptyDataCollection(DataCollection *coll);
void initDataCollection(DataCollection *coll);
void createDataCollection(DataCollection *coll, Data value);
void releaseDataCollection(DataCollection *coll);
void printData(Data d);

#endif
