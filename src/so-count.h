#ifndef SO_COUNT_H

#include <stddef.h>

typedef struct So So;

size_t so_count_ch(So str, char c);
size_t so_count_nch(So str, char c);
size_t so_count_any(So str, So any);
size_t so_count_nany(So str, So any);
size_t so_count_overlap(So a, So b, bool ignorecase);

#define SO_COUNT_H
#endif
