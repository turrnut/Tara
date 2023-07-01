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
 * Implementation of types.h , go there to see more documentation.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "types.h"
#include "../include/constants.h"
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
    if (!IS_BOOLEAN(da)) {
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
    if (left.type != right.type) {
        return false;
    }
    switch (left.type) {
        case BOOLEAN_VALUE:
            return UNPACK_BOOLEAN(left) == UNPACK_BOOLEAN(right);
        case NUMBER_VALUE: 
            return UNPACK_NUMBER(left) == UNPACK_NUMBER(right);
        case NULL_VALUE:
            return (bool)(1);
        case OBJECT_VALUE:
            return UNPACK_OBJECT(left) == UNPACK_OBJECT(right);
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

void empty_map(Map* map) {
    map->count = 0;
    map->volume = 0;
    map->buckets = NULL;
}

void init_map(Map* map) {
    empty_map(map);
}

void free_map(Map* map) {
    freeMemory(Bucket, map->buckets);
    empty_map(map);
}

uint32_t encode(char* chars, int length) {
    uint32_t encoded = HASH_START;
    for (int i = 0; i < length; i++) {
        encoded ^= (uint8_t)chars[i];
        encoded *= HASH_KEY;
    }
    return encoded;
}

Bucket* search_map(Bucket* buckets, int volume, Text* target) {
    uint32_t i = target->encoded % volume;
    Bucket* empty_bucket = NULL;
    while (1) {
        Bucket* bucket = &buckets[i];
        if (bucket->name == NULL) {
            if (IS_NULL(bucket->data)){
                return empty_bucket != NULL ? empty_bucket : bucket;
            } else {
                if (empty_bucket == NULL) {
                    empty_bucket = bucket;
                }
            }
        } else if (bucket->name == target) {
            return bucket;
        }
        i ++;
        i %= volume;
    }
}

void resize_map(Map* map, int volume) {
    Bucket* buckets = ALLOC(Bucket, volume);
    for (int i = 0; i < volume; i++) {
        buckets[i].name = NULL;
        buckets[i].data = PACK_NULL;
    }

    map->count = 0;
    for (int j = 0; j < map->volume; j ++) {
        Bucket* bucket = &map->buckets[j];
        if (bucket->name == NULL)
            continue;
        Bucket* target = search_map(buckets, volume, target->name);
        target->name = bucket->name;
        target->data = bucket->data;
        map->count ++;
    }

    freeMemory(Bucket, map->buckets);
    map->buckets = buckets;
    map->volume = volume;
}

void clone_map(Map* original, Map* clone) {
    for (int i = 0; i < original->volume; i++) {
        Bucket* bucket = &original->buckets[i];
        if (bucket->name != NULL)
            set_map(original, bucket->name, bucket->data);
    }
}

bool delete_map(Map* map, Text* name) {
    bool result = false;
    if (map->count == 0)
        goto retrn;

    Bucket* bucket = search_map(map->buckets, map->volume, name);
    if (bucket->name == NULL)
        goto retrn;

    bucket->name = NULL;
    bucket->data = PACK_BOOLEAN(true);
    result = true;
    retrn:
    return result;
}

bool get_map(Map* map, Text* name, Data* data) {
    if (map->count == 0)
        return false;
    Bucket* bucket = search_map(map->buckets, map->volume, name);
    if (bucket->name == NULL)
        return false;
    else {
        *data = bucket->data;
        return true;
    }
}

bool set_map(Map* map, Text* name, Data data) {
    if (1 + map->count > map->volume * RESIZE_MAP_WHEN_REACHED)
        resize_map(map, stack_alloc(map->volume));
    Bucket* bucket = search_map(map->buckets, map->volume, name);
    bool new = bucket->name == NULL;
    if (new && IS_NULL(bucket->data)) // is it newly created?
        map->count ++;
    bucket->name = name;
    bucket->data = data;
    return new;
}

Text* find_text_in_map(Map* map, const char* ch, int len, uint32_t encoded_txt) {
    if (map->count == 0)
        return NULL;
    uint32_t i = encoded_txt % map->volume;
    while (true) {
        Bucket* current_bucket = &map->buckets[i];
        if (current_bucket->name == NULL) {
            if (IS_NULL(current_bucket->data)) {
                return NULL;
            }
        } else if (current_bucket->name->len == len && current_bucket->name->encoded == encoded_txt && memcmp(current_bucket->name->charlist, ch, len) == 0) {
            return current_bucket->name;
        } else {
            i++;
            i %= map->volume;
        }
    }
}

Text* create_text(const char* c, int last) {
    uint32_t encoded = encode((char*)c,last);
    Text* text = find_text_in_map(&runtime.pool, c, last, encoded);
    if (text != NULL)
        return text;
    char* Heap = ALLOC(char,1+last);
    memcpy(Heap,c,last);
    Heap[last] = '\0';
    return alloc_text(Heap,last,encoded);
}

Text* alloc_text_without_encode(char* c, int l) {
    uint32_t encoded = encode(c, l);
    Text* text = find_text_in_map(&runtime.pool, c, l, encoded);
    if (text != NULL) {
        freeMemory(char, c);
        return text;
    }
    return alloc_text(c, l, encode(c, l));
}

Text* alloc_text(char* c, int last, uint32_t encoded) {
    Text* t = ALLOCOBJ(Text, TEXT);
    t->len = last;
    t->charlist = c;
    t->encoded = encoded;
    set_map(&runtime.pool, t, PACK_NULL);
    return t;
}

void printData(Data d) {
    switch (d.type) {
        case BOOLEAN_VALUE:{
            if (UNPACK_BOOLEAN(d)) printf("true");
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
