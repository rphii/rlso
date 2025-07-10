#ifndef SO_H

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include "endian.h"

#define SO_STACK_CAP    (sizeof(So_Ref) - 1)
#define SO_STACK_THRESH (((size_t)1) << ((sizeof(size_t) - 1) * 8))
#define SO_HEAP_BIT     (((size_t)1) << ((sizeof(size_t)) * 8 - 1))

#define SO_STACK_HEAP_BIT   (((size_t)1) << ((sizeof(unsigned char)) * 8 - 1))

typedef struct So_Heap {
    char *str;
    size_t cap;
} So_Heap;

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

typedef union So {
    So_Stack stack;
    So_Ref ref;
} So;

#define SO_F(s)     (int)(so_len(s)), so_it(s, 0)

bool so_is_stack(So s);
bool so_is_heap(So s);
void so_print_debug(So s);

#define so(str)     so_ll((str), sizeof(str) - 1)
const So so_l(const char *str);
const So so_ll(const char *str, size_t len);
const char so_at(const So s, size_t i);
#define so_it(s, i)    _so_it(&(s), i)
const char *_so_it(const So *s, size_t i);
void so_push(So *s, char c);
void so_extend(So *s, So b);
void so_fmt(So *s, const char *fmt, ...);
void so_fmt_va(So *s, const char *fmt, va_list va);
size_t so_len(So s);
So_Heap *so_heap_base(So s);
void so_clear(So *s);
void so_free(So *s);

#define SO_H
#endif

