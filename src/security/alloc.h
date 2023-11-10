#ifndef alloc_header
#define alloc_header

#include "../include/base.h"

#define MORE_VOLUME(oldVol) ((oldVol) < 16 ? 16 : (oldVol) * 2)
#define MORE_SPACE(t, ptr, oldc, newc) (t*) ralloc(ptr, sizeof(t) * (oldc), sizeof(t) * (newc))
#define FREE_SPACE(t, ptr, old) ralloc(ptr, sizeof(t) * (old), 0)

void* ralloc(void* ptr, size_t old, size_t new);

#endif
