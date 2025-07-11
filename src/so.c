#include "so.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

bool so_is_stack(So s) {
    return (s.stack.len & ~SO_STACK_HEAP_BIT);
}

bool so_is_heap(So s) {
    return (s.ref.len & SO_HEAP_BIT);
}

void so_print_debug(So s) {
    printf("%c[%.*s]%zu", so_is_stack(s) ? 's' : so_is_heap(s) ? 'h' : 'r',
            SO_F(s), so_len(s));
    if(so_is_stack(s)) printf("/%zu", SO_STACK_CAP);
    if(so_is_heap(s)) {
        printf("/%zu", so_heap_base(s)->cap);
        printf("<sizeof:%zu+%zu+%zu>", sizeof(So), sizeof(So_Heap), so_heap_base(s)->cap);
    }
    printf("\n");
}

size_t so_len(So s) {
    if(so_is_stack(s)) return s.stack.len;
    return s.ref.len & ~SO_HEAP_BIT;
}

const So so_l(const char *str) {
    return (const So) {
        .ref.str = (char *)str,
        .ref.len = strlen(str),
    };
}

const So so_ll(const char *str, size_t len) {
    return (const So) {
        .ref.str = (char *)str,
        .ref.len = len,
    };
}

So_Heap *so_heap_grow(So_Heap *heap, size_t cap) {
    size_t cap_old = heap ? heap->cap : 0;
    size_t cap_new = 2 * sizeof(So_Heap);
    while(cap_new < cap) cap_new *= 2;
    if(cap_new <= cap_old) return heap;
    So_Heap *result = realloc(heap, sizeof(*result) + cap_new);
    result->str = (char *)result + sizeof(*result);
    result->cap = cap_new;
    memset(result->str + cap_old, 0, cap_new - cap_old);
    return result;
}

So_Heap *so_heap_base(So s) {
    So_Heap *result = (So_Heap *)((char *)s.ref.str - offsetof(So_Heap, str) - sizeof(So_Heap));
    return result;
}

void so_push(So *s, char c) {
    size_t len = so_len(*s);
    bool is_stack = so_is_stack(*s);
    bool is_heap = so_is_heap(*s);
    if(len + 1 >= SO_HEAP_MAX) exit(1);
    if(len + 1 <= SO_STACK_CAP && !is_heap) {
        if(!is_stack) {
            So_Stack stack;
            memcpy(stack.str, s->ref.str, len);
            s->stack = stack;
        }
        s->stack.str[len] = c;
        s->stack.len = len + 1;
    } else {
        So_Heap *heap = is_heap ? so_heap_base(*s) : 0;
        heap = so_heap_grow(heap, len + 1);
        if(so_is_stack(*s)) memcpy(heap->str, s->stack.str, len);
        s->ref.str = heap->str;
        s->ref.str[len] = c;
        s->ref.len = (len + 1) | SO_HEAP_BIT;
    }
}

void so_extend(So *s, So b) {
    size_t len_a = so_len(*s);
    size_t len_b = so_len(b);
    bool is_stack = so_is_stack(*s);
    bool is_heap = so_is_heap(*s);
    if(len_a + len_b >= SO_HEAP_MAX) exit(1);
    if(len_a + len_b <= SO_STACK_CAP && !is_heap) {
        if(!is_stack) {
            So_Stack stack;
            memcpy(stack.str, s->ref.str, len_a);
            s->stack = stack;
        }
        memcpy(s->stack.str + len_a, so_it(b, 0), len_b);
        s->stack.len = len_a + len_b;
    } else {
        So_Heap *heap = is_heap ? so_heap_base(*s) : 0;
        heap = so_heap_grow(heap, len_a + len_b);
        if(so_is_stack(*s)) memcpy(heap->str, s->stack.str, len_a);
        s->ref.str = heap->str;
        memcpy(s->ref.str + len_a, so_it(b, 0), len_b);
        s->ref.len = (len_a + len_b) | SO_HEAP_BIT;
    }
}

const char so_at(const So s, size_t i) {
    if(so_is_stack(s)) {
        return s.stack.str[i];
    } else {
        return s.ref.str[i];
    }
}

const char *_so_it(const So *s, size_t i) {
    if(so_is_stack(*s)) {
        return &s->stack.str[i];
    } else {
        return &s->ref.str[i];
    }
}

void so_clear(So *s) {
    s->ref.len &= SO_HEAP_BIT;
}

void so_free(So *s) {
    if(so_is_heap(*s)) free(so_heap_base(*s));
    memset(s, 0, sizeof(*s));
}

