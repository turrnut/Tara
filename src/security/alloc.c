#include <stdlib.h>
#include "alloc.h"

void *ralloc(void* ptr, size_t old, size_t new) {
    if (new == 0) {
        free(ptr);
        return NULL;
    }
    void* res = realloc(ptr, new);
    if (res == NULL) exit(1);
    return res;
}
