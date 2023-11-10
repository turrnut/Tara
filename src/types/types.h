#ifndef types_header
#define types_header

#include "../include/base.h"

typedef double DataValue;

typedef struct {
    int volume;
    int counter;
    DataValue* data;
} DataValuesList;

void emptyDataValuesList (DataValuesList* list);
void initDataValuesList (DataValuesList* list);
void writeDataValuesList (DataValuesList* list, DataValue val);
void freeDataValuesList (DataValuesList* list);

#endif
