#ifndef SO_H

#include "endian.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h> /* strlen */

#define SO_STACK_CAP    (sizeof(So_Ref) - 1)
#define SO_STACK_HEAP_BIT   (((size_t)1) << ((sizeof(unsigned char)) * 8 - 1))

typedef struct So_Ref {
#if defined(ENDIAN_BIG)
    size_t len;
    char *str;
#else
    char *str;
    size_t len;
#endif
} So_Ref;

typedef struct So_Stack {
#if defined(ENDIAN_BIG)
    unsigned char len;
    char str[SO_STACK_CAP];
#else
    char str[SO_STACK_CAP];
    unsigned char len;
#endif
} So_Stack;

typedef struct So {
    union {
        So_Stack stack;
        So_Ref ref;
    };
} So;

#define SO_F(s)     (int)(so_len(s)), so_it0(s)

bool so_is_stack(So s);
bool so_is_heap(So s);
void so_print_debug(So s);

#define so(s)           (So){ .ref.str = (s), .ref.len = sizeof((s)) - 1 }
#define so_l(s)         (So){ .ref.str = (s), .ref.len = (s) ? strlen((s)) : 0 }
#define so_ll(s, l)     (So){ .ref.str = (s), .ref.len = (l) }

const char  so_at(So s, size_t i);
const char _so_at(So *s, size_t i);
const char  so_at0(So s);
const char _so_at0(So *s);
#define     so_it(s, i) _so_it(&(s), i)
char *      _so_it(So *s, size_t i);
#define     so_it0(s) _so_it0(&(s))
char *     _so_it0(So *s);
#define     so_i0(s, i0)        so_ll(so_it(s, i0), so_len(s) - i0)
#define    _so_i0(s, i0)        so_ll(_so_it(s, i0), _so_len(s) - i0)
#define     so_iE(s, iE)        so_ll(so_it0(s), iE)
#define    _so_iE(s, iE)        so_ll(_so_it0(s), iE)
#define     so_sub(s, i0, iE)   so_ll(so_it(s, i0), so_len(s) - (iE - i0))
#define    _so_sub(s, i0, iE)   so_ll(_so_it(s, i0), _so_len(s) - (iE - i0))
void        so_push(So *s, char c);
void        so_extend(So *s, So b);
void        so_resize(So *s, size_t len);
void        so_fmt(So *s, const char *fmt, ...);
void        so_fmt_va(So *s, const char *fmt, va_list va);
size_t      so_len(So s);
size_t     _so_len(So *s);
void        so_copy(So *s, So b);
So          so_clone(So b);
void        so_clear(So *s);
void        so_free(So *s);

#define SO_H
#endif

