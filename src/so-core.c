#include "so-core.h"
#include "so-heap.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <rl/err.h>

static bool _so_is_heap(So *s);
static void so_resize_known(So *s, size_t len_old, size_t len_new);

static char *so_grow_by_heap(So *so, size_t len_add);
static char *so_grow_by_ref(So *so, size_t len_add);
static char *so_grow_by(So *so, size_t len_add);

static char *so_grow_by_heap(So *so, size_t len_add) {
    size_t len_was = so->len;
    So_Heap *heap = so_heap_base(so);
    if(len_was + len_add >= heap->cap) {
        heap = so_heap_grow(heap, len_was + len_add);
        so->str = heap->str;
    }
    so->len = (len_was + len_add);
    so->is_heap = true;
    return so->str + len_was;
}

static char *so_grow_by_ref(So *so, size_t len_add) {
    size_t len_was = so->len;
    So_Heap *heap = so_heap_grow(0, len_was + len_add);
    memcpy(heap->str, so->str, len_was);
    so->str = heap->str;
    so->len = (len_was + len_add);
    so->is_heap = true;
    return so->str + len_was;
}
#include "so-print.h"

static char *so_grow_by(So *so, size_t len_add) {
    ASSERT_ARG(len_add);
    if(_so_is_heap(so)) {
        return so_grow_by_heap(so, len_add);
    } else {
        return so_grow_by_ref(so, len_add);
    }
}

bool so_is_empty(So s) {
    return !so_len(s);
}

bool so_is_zero(So s) {
    return !s.str && !s.len;
}

bool so_is_heap(So so) {
    return so.is_heap;
}

static bool _so_is_heap(So *so) {
    return so->is_heap;
}

size_t so_len(So s) {
    return s.len;
}

void so_set_len(So *so, size_t len) {
    so->len = len;
}

void so_change_len(So *so, size_t len) {
    so->len += len;
}


void so_copy(So *so, So b) {
    so_clear(so);
    if(!b.len) return;
    //so_resize_known(s, 0, ref.len);
    memcpy(so_grow_by(so, b.len), b.str, so->len);
}

//#include "so-print.h"

So so_clone(So b) {
    So result = {0};
    if(b.len) {
        memcpy(so_grow_by(&result, b.len), so_it0(b), b.len);
    }
    //so_printdbg(result);
    return result;
}

char *so_dup(So so) {
    So ref = so;
    char *result = malloc(ref.len + 1);
    memcpy(result, ref.str, ref.len);
    result[ref.len] = 0;
    return result;
}

void so_push(So *s, char c) {
    *so_grow_by(s, 1) = c;
}

void so_extend(So *so, So b) {
    So ref = b;
    if(!ref.len) return;
    //printff("EXTEND[%.*s]BY[%.*s]",SO_F(*so),SO_F(b));
    if(_so_is_heap(so) && so_is_heap(b)) {
        So_Heap *heap = so_heap_base(so);
        if(b.str >= heap->str && b.str <= heap->str + heap->cap) {
            /* memory overlaps - just get a new heap and free the old one */
            So_Heap *neo = so_heap_grow(0, so->len + b.len);
            memcpy(neo->str, so->str, so->len);
            memcpy(neo->str + so->len, b.str, b.len);
            so->len += b.len;
            so->str = neo->str;
            so->is_heap = true; /* not needed */
            free(heap);
        } else {
            /* memory does not overlap */
            char *s0 = so_grow_by_heap(so, b.len);
            memcpy(s0, b.str, b.len);
        }
    } else {
        char *s0 = so_grow_by(so, b.len);
        memcpy(s0, b.str, b.len);
    }
}

void so_resize_known(So *s, size_t len_old, size_t len_new) {
    bool is_heap = so_is_heap(*s);
    if(len_new > len_old) {
        //// TODO? if(len_new >= SO_HEAP_MAX) exit(1);
        so_grow_by(s, len_new - len_old);
    } else if(len_new < len_old) {
        s->len = len_new;
    }
}

void so_resize(So *s, size_t len_new) {
    size_t len_old = so_len(*s);
    so_resize_known(s, len_old, len_new);
}

void so_fmt(So *s, const char *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    so_fmt_va(s, fmt, va);
    va_end(va);
}

void so_fmt_va(So *s, const char *fmt, va_list va) {
    va_list argp2;
    va_copy(argp2, va);
    size_t len_app = (size_t)vsnprintf(0, 0, fmt, argp2);
    va_end(argp2);

#if 0
    if((int)len_app < 0) {
        ABORT("len_app is < 0!");
    }
#endif

    /* calculate required memory */
    So old = *s;
    size_t len_new = old.len + len_app;
    so_grow_by(s, len_app + 1);
    so_resize(s, len_new);
    So new = *s;

    if(len_new) {
        /* actual append */
        ASSERT_ARG(s);
        //ASSERT_ARG(_so_it(s, old.len));
        //printf("IS_STACK %u, IS_HEAP %u\n", _so_is_stack(s), _so_is_heap(s));
        int len_chng = vsnprintf(new.str + old.len, len_app + 1, fmt, va);
    }

#if 0
    // check for success
    if(!(len_chng >= 0 && (size_t)len_chng <= len_app)) {
        ABORT("len_chng is < 0!");
    }
#endif
}

const char so_at(So so, size_t i) {
    ASSERT_ARG(i < so.len);
    return so.str[i];
}

const char so_at0(So s) {
    return *s.str;
}

char *so_it0(So so) {
    return so.str;
}

char *so_itE(So so) {
    return so.str + so.len;
}

char *so_it(So so, size_t i) {
    ASSERT_ARG(i <= so.len);
    return so.str + i;
}

So so_i0(So so, size_t i0) { 
    ASSERT_ARG(i0 <= so.len);
    return (So){ .str = so.str + i0, .len = so.len - i0 };
}

So so_iE(So so, size_t iE) {
    ASSERT_ARG(iE <= so.len);
    return (So){ .str = so.str, .len = iE };
}

So so_sub(So so, size_t i0, size_t iE) {
    ASSERT_ARG(i0 <= so.len);
    ASSERT_ARG(iE <= so.len);
    return (So){ .str = so.str + i0, .len = (iE - i0) };
}

size_t so_shift(So *so, size_t shift) {
    ASSERT_ARG(shift <= so->len);
    so->str += shift;
    so->len = (so->len - shift);
    so->is_heap = false;
    return shift;
}

void so_clear(So *so) {
    so->len = 0;
}

void so_free_v(So so) {
    so_free(&so);
}

void so_free(So *so) {
    if(!so) return;
    if(so_is_heap(*so)) free(so_heap_base(so));
    memset(so, 0, sizeof(*so));
}

#if 0 
void so_1buf_old(So *so, size_t *index) {
    ASSERT_ARG(so);
    ASSERT_ARG(index);
    *index = so->len;
}

void so_1buf_new(So *so, size_t *index) {
    ASSERT_ARG(so);
    ASSERT_ARG(index);
    if(!*index) return;
    size_t len_old = *index;
    size_t len_new = so->len - len_old;
    //printff("onebuf new %zu->%zu (%zu)",len_old,ref.len,len_new);
    //printff("i0 %zu[%.*s] / iBUF %zu[%.*s]", len_old, ref.str, ref.str, len_new, ref.str + len_old, ref.str + len_old);
    memmove(so->str, so->str + len_old, len_new);
    //memmove(_so_it0(so), _so_it(so, len_old), len_new);
    so_resize(so, len_new);
    *index = 0;
}
#endif

