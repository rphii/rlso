#ifndef SO_ALIGN_H

#include "so-core.h"
#include <stddef.h>

typedef struct So_Alig_Cachen {
    So fmt;
    size_t progress;
    size_t i0_prev;
    size_t lines_done;
} So_Align_Cache;

typedef struct So_Align {
    So_Align_Cache *cache;
    size_t i0;
    size_t iNL;
    size_t iE;
    size_t n_lines;
} So_Align;

void so_extend_al(So *out, So_Align al, So add);
void so_fmt_al(So *out, So_Align al, char *format, ...);

void so_al_config(So_Align *al, size_t i0, size_t iNL, size_t iE, size_t n_lines, So_Align_Cache *cache);
void so_al_cache_rewind(So_Align_Cache *c);
void so_al_cache_clear(So_Align_Cache *c);
void so_al_cache_free(So_Align_Cache *c);

#define SO_ALIGN_H
#endif

