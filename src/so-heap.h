#ifndef SO_HEAP_H

#include <stddef.h>

#define SO_HEAP_MAX     (((size_t)1) << ((sizeof(size_t) - 1) * 8))
#define SO_HEAP_BIT     (((size_t)1) << ((sizeof(size_t)) * 8 - 1))

typedef struct So_Heap {
    char *str;
    size_t cap : 8 * (sizeof(size_t) - sizeof(unsigned char));
    unsigned char flags;
} So_Heap;

struct So;

So_Heap *so_heap_grow(So_Heap *heap, size_t cap);
So_Heap *so_heap_base(struct So s);

#define SO_HEAP_H
#endif

