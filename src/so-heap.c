#include "so-heap.h"

#include "so.h"

#include <stdlib.h>
#include <stdio.h>

So_Heap *so_heap_grow(So_Heap *heap, size_t cap) {
    printf(">>>GROW HEAP:%p TO:%zu\n",heap,cap);
    size_t cap_old = heap ? heap->cap : 0;
    if(cap <= cap_old) return heap;
    size_t cap_new = 2 * sizeof(So_Heap);
    while(cap_new < cap) cap_new *= 2;
    So_Heap *result = realloc(heap, sizeof(*result) + cap_new);
    result->str = (char *)result + sizeof(*result);
    result->cap = cap_new;
    //memset(result->str + cap_old, 0, cap_new - cap_old);
    printf(">>>GROWN HEAP:%p TO:%zu\n",result,cap);
    return result;
}

So_Heap *so_heap_base(struct So *s) {
    So_Heap *result = (So_Heap *)((char *)s->str - offsetof(So_Heap, str) - sizeof(So_Heap));
    return result;
}

