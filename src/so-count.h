#ifndef SO_COUNT_H

#include <stdbool.h>
#include <stddef.h>

#include "so-cmp-attr.h"

typedef struct So So;
typedef struct So_Ref So_Ref;

size_t so_count_ch(So str, char c);
size_t so_count_nch(So str, char c);
size_t so_count_any(So str, So any);
size_t so_count_nany(So str, So nany);
size_t so_count_overlapx(So a, So b, So_Cmp_Attr attr);

size_t _so_count_ch(So_Ref ref, char c);
size_t _so_count_nch(So_Ref ref, char c);
size_t _so_count_any(So_Ref ref, So_Ref any);
size_t _so_count_nany(So_Ref ref, So_Ref nany);
size_t _so_count_overlapx(So_Ref ra, So_Ref rb, So_Cmp_Attr attr);

#define SO_COUNT_H
#endif
