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
 * type.c
 * Implementation of type.h , go there to see more documentation.
 */

#include <stdio.h>
#include <string.h>
#include "type.h"
#include "../runtime/runtime.h"
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

Type get_object_type(Data obj) {
    return UNPACK_OBJECT(obj)->object_t;
}

bool isType(Data d, Type t) {
    return ((bool)(UNPACK_OBJECT(d)->object_t == t && IS_OBJECT(d)));
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

const char* get_str_from_type_name(DataType dat) {
    switch (dat)
    {
        case NUMBER_VALUE:return "number";
        case BOOLEAN_VALUE:return "boolean";
        case NULL_VALUE:return "null";
        case OBJECT_VALUE:
        default: return "object";
    }
}

bool isFalse (Data da) {
    if(!IS_BOOLEAN(da)) {
        if (IS_NULL(da)) return true;
        if (IS_NUMBER(da)) {
            if (UNPACK_NUMBER(da) == 0) return true;
            return false;
        } 
    } else {
        if (!UNPACK_BOOLEAN(da)) return true;
        return false;
    }
}

bool objectsEqual(Data left, Data right) {
    return (UNPACK_TEXT(left)->len == UNPACK_TEXT(right)->len) && (memcmp(UNPACK_TEXT(left)->charlist,UNPACK_TEXT(right)->charlist, UNPACK_TEXT(left)->len));
}

const char* getDataNameByType(DataType dat) {
    switch(dat) {
        case BOOLEAN_VALUE:
            return "boolean";
        case NULL_VALUE:
            return "null";
        case NUMBER_VALUE:
            return "number";
        case OBJECT_VALUE:
        default: return "object";
    }
}

bool isEqual(Data left, Data right) {
    if(left.type != right.type) {
        return false;
    }
    switch (left.type) {
        case BOOLEAN_VALUE:
            return UNPACK_BOOLEAN(left) == UNPACK_BOOLEAN(right);
        case NUMBER_VALUE: 
            return UNPACK_NUMBER(left) == UNPACK_NUMBER(right);
        case NULL_VALUE: return (bool)(1);
        case OBJECT_VALUE: return objectsEqual(left, right);
        default: return false;
    }
}

Object* allocobj(size_t size, Type type) {
    Object* obj = (Object*)reallocMemory(NULL,size);
    obj->object_t = type;
    obj->ref = (struct Object*)runtime.heap;

    runtime.heap = obj;
    return obj;
}

Text* create_text(const char* c, int last) {
    char* Heap = ALLOC(char,1+last);
    memcpy(Heap,c,last);
    Heap[last] = '\0';
    return allocText(Heap,last);
}

Text* allocText(char* c, int last) {
    Text* t = ALLOCOBJ(Text, TEXT);
    t->len = last;
    t->charlist = c;
    return t;
}

void printData(Data d) {
    switch (d.type) {
        case BOOLEAN_VALUE:{
            if(UNPACK_BOOLEAN(d)) printf("true");
            else printf("false");
            break;
        }
        case NULL_VALUE:{
            printf("null");
            break;
        }
        case NUMBER_VALUE:{
            printf("%g", UNPACK_NUMBER(d));
            break;
        }

        case OBJECT_VALUE: {
            switch (get_object_type(d)) {
                case TEXT:
                    printf("%s", UNPACK_TEXT_AS_C_CHARS(d));
                    break;
                
                default:
                    break;
            }
            break;
        }

        default:{
            break;
        }
    }
}
