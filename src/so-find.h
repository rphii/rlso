#ifndef SO_FIND_H

#include "so-cmp-attr.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct So So;
typedef struct So_Ref So_Ref;

size_t  so_find_f(So so, size_t *out_iE);
size_t  so_find_ch(So so, char c);
size_t _so_find_ch(So_Ref ref, char c);
size_t  so_find_nch(So so, char c);
size_t _so_find_nch(So_Ref ref, char c);
size_t  so_find_ws(So so);
size_t  so_find_nws(So so);
size_t  so_find_any(So so, So any);
size_t  so_find_nany(So so, So any);
size_t  so_find_sub(So so, So sub, So_Cmp_Attr attr);
size_t _so_find_sub(So_Ref ref, So sub, So_Cmp_Attr attr);
size_t  so_find_nsub(So so, So sub, So_Cmp_Attr attr);
size_t _so_find_nsub(So_Ref, So sub, So_Cmp_Attr attr);

size_t  so_rfind_f(So so, size_t *out_iE);
size_t  so_rfind_f0(So so, So *fmt);
size_t  so_rfind_ch(So so, char c);
size_t _so_rfind_ch(So_Ref ref, char c);
size_t  so_rfind_nch(So so, char c);
size_t _so_rfind_nch(So_Ref ref, char c);
size_t  so_rfind_ws(So so);
size_t  so_rfind_nws(So so);
size_t  so_rfind_any(So so, So any);
size_t  so_rfind_nany(So so, So any);
size_t  so_rfind_sub(So so, So sub, So_Cmp_Attr attr);
size_t _so_rfind_sub(So_Ref ref, So sub, So_Cmp_Attr attr);
size_t  so_rfind_nsub(So so, So sub, So_Cmp_Attr attr);
size_t _so_rfind_nsub(So_Ref ref, So sub, So_Cmp_Attr attr);

#define SO_FIND_H
#endif

