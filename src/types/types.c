#include <stdio.h>
#include <stdlib.h>
#include "../security/alloc.h"
#include "types.h"


void emptyDataValuesList (DataValuesList* list) {
    list->volume = 0;
    list->counter = 0;
    list->data = NULL;
}
void initDataValuesList (DataValuesList* list) {
    emptyDataValuesList(list);
}
void writeDataValuesList (DataValuesList* list, DataValue val) {
    if (list->volume < list->counter + 1) {
        int oldVolume = list->volume;
        list->volume = MORE_VOLUME(oldVolume);
        list->data = MORE_SPACE(DataValue, list->data, oldVolume, list->volume);
    }
    list->data[list->counter] = val;
    list->counter++;
}
void freeDataValuesList (DataValuesList* list) {
    FREE_SPACE(DataValue, list->data, list->volume);
    emptyDataValuesList(list);
}
