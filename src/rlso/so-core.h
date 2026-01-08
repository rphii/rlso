#ifndef SO_CORE_H

#include "so-heap.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h> /* strlen */

#define SO_STACK_CAP        (sizeof(So_Ref) - 1)
#define SO_STACK_HEAP_BIT   (((size_t)1) << ((sizeof(unsigned char)) * 8 - 1))

typedef struct So {
    char *str;
    size_t is_heap  : +1;
    size_t len      : -1+8*sizeof(size_t);
} So;

#define SO          (So){.str = 0, .len = 0}
#define SO_F(so)    (int)(so_len((so))), so_it0((so))

bool        so_is_empty(So so);
bool        so_is_zero(So so);
bool        so_is_heap(So so);

#define     so(so)               ((So){ .str = (so), .len = (so) ? sizeof((so)) - 1 : 0 })
#define     so_l(so)             ((So){ .str = (so), .len = (so) ? strlen((so)) : 0 })
#define     so_ll(so, l)         ((So){ .str = (so), .len = (l) })

const char  so_at(So so, size_t i);
const char  so_at0(So so);
const char  so_atE(So so);
char *      so_it(So so, size_t i);
char *      so_it0(So so);
char *      so_itE(So so);
So          so_i0(So so, size_t i0);
So          so_iE(So so, size_t iE);
So          so_sub(So so, size_t i0, size_t iE);
size_t      so_shift(So *so, size_t shift);
void        so_push(So *so, char c);
void        so_extend(So *so, So b);
void        so_resize(So *so, size_t len);
void        so_fmt(So *so, const char *fmt, ...);
void        so_fmt_va(So *so, const char *fmt, va_list va);
size_t      so_len(So so);
void        so_copy(So *so, So b);
So          so_clone(So b);
char *      so_dup(So so);
void        so_clear(So *so);
void        so_free(So *so);
void        so_free_v(So so);
void        so_zero(So *so);
size_t      so_writefunc(void *ptr, size_t size, size_t nmemb, So *str);
void        so_1buf_old(So *so, size_t *index);
void        so_1buf_new(So *so, size_t *index);

#if 0
#define     so_ref(so) _so_ref(&(so))
#endif

#define SO_CORE_H
#endif

