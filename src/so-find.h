#ifndef SO_FIND_H

#include "so-cmp-attr.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct So So;

size_t so_find_f(So str, size_t *out_iE);
size_t so_find_ch(So str, char c);
size_t so_find_nch(So str, char c);
size_t so_find_ws(So str);
size_t so_find_nws(So str);
size_t so_find_any(So str, So any);
size_t so_find_nany(So str, So any);
size_t so_find_sub(So str, So sub, So_Cmp_Attr attr);
size_t so_find_nsub(So str, So sub, So_Cmp_Attr attr);

size_t so_rfind_f(So str, size_t *out_iE);
size_t so_rfind_ch(So str, char c);
size_t so_rfind_nch(So str, char c);
size_t so_rfind_ws(So str);
size_t so_rfind_nws(So str);
size_t so_rfind_any(So str, So any);
size_t so_rfind_nany(So str, So any);
size_t so_rfind_sub(So str, So sub, So_Cmp_Attr attr);
size_t so_rfind_nsub(So str, So sub, So_Cmp_Attr attr);

#define SO_FIND_H
#endif

