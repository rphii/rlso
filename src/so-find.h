#ifndef SO_FIND_H

#include "so-cmp-attr.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct So So;
typedef struct So_Ref So_Ref;

size_t _so_find_ch(So_Ref ref, char c);
size_t _so_find_nch(So_Ref ref, char c);
size_t _so_find_ws(So_Ref ref);
size_t _so_find_nws(So_Ref ref);
size_t _so_find_any(So_Ref ref, So_Ref any);
size_t _so_find_nany(So_Ref ref, So_Ref nany);
size_t _so_find_sub(So_Ref ref, So_Ref sub, bool ignorecase);

size_t  so_find_ch(So so, char c);
size_t  so_find_nch(So so, char c);
size_t  so_find_ws(So so);
size_t  so_find_nws(So so);
size_t  so_find_any(So so, So any);
size_t  so_find_nany(So so, So nany);
size_t  so_find_sub(So so, So sub, bool ignorecase);

size_t _so_rfind_ch(So_Ref ref, char c);
size_t _so_rfind_nch(So_Ref ref, char c);
size_t _so_rfind_ws(So_Ref ref);
size_t _so_rfind_nws(So_Ref ref);
size_t _so_rfind_any(So_Ref ref, So_Ref any);
size_t _so_rfind_nany(So_Ref ref, So_Ref nany);
size_t _so_rfind_sub(So_Ref ref, So_Ref sub, bool ignorecase);

size_t  so_rfind_ch(So so, char c);
size_t  so_rfind_nch(So so, char c);
size_t  so_rfind_ws(So so);
size_t  so_rfind_nws(So so);
size_t  so_rfind_any(So so, So any);
size_t  so_rfind_nany(So so, So nany);
size_t  so_rfind_sub(So so, So sub, bool ignorecase);

/* weird stuff */
size_t  so_find_f(So so, size_t *out_iE);
size_t  so_rfind_f(So so, size_t *out_iE);
size_t  so_rfind_f0(So so, So *fmt);

#define SO_FIND_H
#endif

