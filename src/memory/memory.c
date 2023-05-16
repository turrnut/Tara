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
 * memory.c
 *
 */

#include <stdlib.h>
#include "memory.h"

int allocVolume(int vol)
{

    return ((vol) < 4 ? 4 : (vol)*1.5);
}

void *reallocMemory(void *ptr, size_t targetAmount)
{

    if (targetAmount == 0)
    {
        free(ptr);
        return NULL;
    }

    void *ret = realloc(ptr, targetAmount);

    // exit when there is no more space to allocate
    if (ret == NULL)
        exit(1);
    return ret;
}
