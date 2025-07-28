#include "so.h"
#include "so-heap.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <rl/err.h>

static void so_resize_known(So *s, size_t len_old, size_t len_new);

static char *so_grow_by_stack(So *so, size_t len_add);
static char *so_grow_by_heap(So *so, size_t len_add);
static char *so_grow_by_ref(So *so, size_t len_add);
static char *so_grow_by(So *so, size_t len_add);
static bool _so_is_stack(So *s);
static bool _so_is_heap(So *s);

static char *so_grow_by_stack(So *so, size_t len_add) {
    size_t len_was = so->stack.len;
    if(len_was + len_add <= SO_STACK_CAP) {
        so->stack.len += len_add;
        return so->stack.str + len_was;
    } else {
        So_Heap *heap = so_heap_grow(0, len_was + len_add);
        memcpy(heap->str, so->stack.str, len_was);
        so->ref.str = heap->str;
        so->ref.len = (len_was + len_add) | SO_HEAP_BIT;
        return so->ref.str + len_was;
    }
}

static char *so_grow_by_heap(So *so, size_t len_add) {
    size_t len_was = so->ref.len & ~SO_HEAP_BIT;
    So_Heap *heap = so_heap_base(so);
    if(len_was + len_add >= heap->cap) {
        heap = so_heap_grow(heap, len_was + len_add);
        so->ref.str = heap->str;
    }
    so->ref.len = (len_was + len_add) | SO_HEAP_BIT;
    return so->ref.str + len_was;
}

static char *so_grow_by_ref(So *so, size_t len_add) {
    size_t len_was = so->ref.len;
    if(len_was + len_add <= SO_STACK_CAP) {
        memmove(so->stack.str, so->ref.str, len_was);
        so->stack.len = len_was + len_add;
        return so->stack.str + len_was;
    } else {
        So_Heap *heap = so_heap_grow(0, len_was + len_add);
        memcpy(heap->str, so->ref.str, len_was);
        so->ref.str = heap->str;
        so->ref.len = (len_was + len_add) | SO_HEAP_BIT;
        return so->ref.str + len_was;
    }
}

static char *so_grow_by(So *so, size_t len_add) {
    if(_so_is_stack(so)) {
        return so_grow_by_stack(so, len_add);
    } else if(_so_is_heap(so)) {
        return so_grow_by_heap(so, len_add);
    } else {
        return so_grow_by_ref(so, len_add);
    }
}

bool so_is_empty(So s) {
    return !so_len(s);
}

bool so_is_zero(So s) {
    return !s.ref.str && !s.ref.len;
}

bool so_is_stack(So s) {
    return (s.stack.len & ~SO_STACK_HEAP_BIT);
}

static bool _so_is_stack(So *s) {
    return (s->stack.len & ~SO_STACK_HEAP_BIT);
}

bool so_is_heap(So s) {
    return (s.ref.len & SO_HEAP_BIT);
}

static bool _so_is_heap(So *s) {
    return so_is_heap(*s);
}

size_t so_len(So s) {
    if(so_is_stack(s)) return s.stack.len;
    return s.ref.len & ~SO_HEAP_BIT;
}

size_t _so_len(So *s) {
    return so_len(*s);
}

void so_set_len(So *so, size_t len) {
    if(_so_is_stack(so)) {
        so->stack.len = len;
    } else if(_so_is_heap(so)) {
        so->ref.len = len | SO_HEAP_BIT;
    } else {
        so->ref.len = len;
    }
}

void so_change_len(So *so, size_t len) {
    if(_so_is_stack(so)) {
        so->stack.len += len;
    } else if(_so_is_heap(so)) {
        so->ref.len += len;
        so->ref.len |= SO_HEAP_BIT;
    } else {
        so->ref.len += len;
    }
}


void so_copy(So *s, So b) {
    so_clear(s);
    size_t len = so_len(b);
    so_resize_known(s, 0, len);
    memcpy(_so_it0(s), so_it0(b), len);
}

//#include "so-print.h"

So so_clone(So b) {
    So result = {0};
    size_t len = so_len(b);
    //printff("CLONE:[%.*s]", SO_F(b));
    memcpy(so_grow_by(&result, len), so_it0(b), len);
    //so_printdbg(result);
    return result;
}

char *so_dup(So so) {
    So_Ref ref = so_ref(so);
    char *result = malloc(ref.len + 1);
    memcpy(result, ref.str, ref.len);
    result[ref.len] = 0;
    return result;
}

void so_push(So *s, char c) {
    *so_grow_by(s, 1) = c;
}

void so_extend(So *s, So b) {
    So_Heap *heap = 0;
    So_Ref ref = so_ref(b);
    if(so_is_heap(b) && _so_is_heap(s) && b.ref.str == s->ref.str) {

        heap = so_heap_grow(0, ref.len);
        ref.str = heap->str;
    }
    memcpy(so_grow_by(s, ref.len), ref.str, ref.len);
    if(heap) free(heap);
}

void so_resize_known(So *s, size_t len_old, size_t len_new) {
    bool is_stack = so_is_stack(*s);
    bool is_heap = so_is_heap(*s);
    if(len_new > len_old) {
        if(len_new >= SO_HEAP_MAX) exit(1);
        if(len_new <= SO_STACK_CAP && !is_heap) {
            if(!is_stack) {
                So_Stack stack;
                memcpy(stack.str, s->ref.str, len_old);
                s->stack = stack;
            }
            s->stack.len = len_new;
        } else {
            so_grow_by(s, len_new - len_old);
        }
    } else if(len_new < len_old) {
        if(is_stack) s->stack.len = len_new;
        else s->ref.len = len_new | (is_heap ? SO_HEAP_BIT : 0);
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
    size_t len_old = so_len(*s);
    size_t len_new = len_old + len_app;
    so_grow_by(s, len_app + 1);
    so_resize(s, len_new);

    if(len_new) {
        /* actual append */
        ASSERT_ARG(s);
        ASSERT_ARG(_so_it(s, len_old));
        //printf("IS_STACK %u, IS_HEAP %u\n", _so_is_stack(s), _so_is_heap(s));
        int len_chng = vsnprintf(_so_it(s, len_old), len_app + 1, fmt, va);
    }

#if 0
    // check for success
    if(!(len_chng >= 0 && (size_t)len_chng <= len_app)) {
        ABORT("len_chng is < 0!");
    }
#endif
}

const char so_at(So s, size_t i) {
    return so_is_stack(s) ? s.stack.str[i] : s.ref.str[i];
}

const char _so_at(So *s, size_t i) {
    return so_at(*s, i);
}

const char so_at0(So s) {
    return so_is_stack(s) ? s.stack.str[0] : s.ref.str[0];
}

const char _so_at0(So *s) {
    return so_at0(*s);
}


char *_so_it0(So *s) {
    return so_it0(*s);
}

char *_so_it(So *s, size_t i) {
    return so_it(*s, i);
}

So _so_i0(So *s, size_t i0) { 
    return so_i0(*s, i0);
}

So _so_iE(So *s, size_t iE) {
    return so_iE(*s, iE);
}

So _so_sub(So *s, size_t i0, size_t iE) {
    return so_sub(*s, i0, iE);
}

So_Ref _so_ref(So *s) {
    return so_ref(*s);
}


void so_clear(So *s) {
    s->ref.len &= SO_HEAP_BIT;
}

void so_free(So *s) {
    if(so_is_heap(*s)) free(so_heap_base(s));
    memset(s, 0, sizeof(*s));
}

void so_1buf_old(So *so, size_t *index) {
    ASSERT_ARG(so);
    ASSERT_ARG(index);
    *index = _so_len(so);
}

void so_1buf_new(So *so, size_t *index) {
    ASSERT_ARG(so);
    ASSERT_ARG(index);
    if(!*index) return;
    So_Ref ref = _so_ref(so);
    size_t len_old = *index;
    size_t len_new = ref.len - len_old;
    //printff("onebuf new %zu->%zu (%zu)",len_old,ref.len,len_new);
    //printff("i0 %zu[%.*s] / iBUF %zu[%.*s]", len_old, ref.str, ref.str, len_new, ref.str + len_old, ref.str + len_old);
    memmove(ref.str, ref.str + len_old, len_new);
    //memmove(_so_it0(so), _so_it(so, len_old), len_new);
    so_resize(so, len_new);
    *index = 0;
}


