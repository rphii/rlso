#ifndef SO_H

#include <rl/endian-detect.h>

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h> /* strlen */

#define SO_STACK_CAP        (sizeof(So_Ref) - 1)
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

#define SO_F(s)     (int)(so_len((s))), so_it0((s))

bool        so_is_empty(So s);
bool        so_is_zero(So s);
bool        so_is_stack(So s);
bool        so_is_heap(So s);

#define     so(s)           (So){ .ref.str = (s), .ref.len = (s) ? sizeof((s)) - 1 : 0 }
#define     so_l(s)         (So){ .ref.str = (s), .ref.len = (s) ? strlen((s)) : 0 }
#define     so_ll(s, l)     (So){ .ref.str = (s), .ref.len = (l) }

const char  so_at(So s, size_t i);
const char _so_at(So *s, size_t i);
const char  so_at0(So s);
const char _so_at0(So *s);
#define     so_it(s, i)         (so_is_stack((s)) ? (s).stack.str + (i) : (s).ref.str + (i))
char *     _so_it(So *s, size_t i);
#define     so_it0(s)           (so_is_stack((s)) ? (s).stack.str : (s).ref.str)
char *     _so_it0(So *s);
#define     so_i0(s, i0)        so_ll(so_it((s), i0), so_len((s)) - i0)
So         _so_i0(So *s, size_t i0);
#define     so_iE(s, iE)        so_ll(so_it0((s)), iE)
So         _so_iE(So *s, size_t iE);
#define     so_sub(s, i0, iE)   so_ll(so_it(s, i0), so_len((s)) - (iE - i0))
So         _so_sub(So *s, size_t i0, size_t iE);
#define     so_ref(s)           (so_is_stack((s)) ? (So_Ref){ .str = (s).stack.str, .len = (s).stack.len } : (So_Ref){ .str = (s).ref.str, .len = (s).ref.len })
So_Ref     _so_ref(So *s);
void        so_push(So *s, char c);
void        so_extend(So *s, So b);
void        so_resize(So *s, size_t len);
void        so_fmt(So *s, const char *fmt, ...);
void        so_fmt_va(So *s, const char *fmt, va_list va);
size_t      so_len(So s);
size_t     _so_len(So *s);
void        so_copy(So *s, So b);
So          so_clone(So b);
char *      so_dup(So so);
void        so_clear(So *s);
void        so_free(So *s);
void        so_1buf_old(So *so, size_t *index);
void        so_1buf_new(So *so, size_t *index);

#if 0
#define     so_ref(s) _so_ref(&(s))
#endif

#define SO_H
#endif

