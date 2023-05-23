/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 *
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE for more details about
 * how you can use it, you have freedom to distribute and
 * use this code in your project. However, you will have to
 * state changes you made and include the orginal author of
 * this code.
 *
 * memory.h
 *
 */
#ifndef memory_header
#define memory_header

#define increaseMemory(type, pointer, target) \
    (type *)reallocMemory(pointer,            \
                          sizeof(type) * (target))

#define freeMemory(type, pointer) \
    reallocMemory(pointer, 0)

int allocVolume(int vol);
void *reallocMemory(void *pointer, size_t targetAmount);

#endif
