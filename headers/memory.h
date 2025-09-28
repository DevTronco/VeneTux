#include "utils.h"

#ifndef MEMORY_H
#define MEMORY_H

static inline int memcmp(const void *a, const void *b, size_t n) {
    const uint8_t *pa = (const uint8_t *) a;
    const uint8_t *pb = (const uint8_t *) b; 
    for (size_t i = 0; i < n; i++) {
        if (pa[i] != pb[i])
            return pa[i] - pb[i];
    }
    return 0;
}

#endif