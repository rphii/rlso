#ifndef SO_ALIGN_H

#include "so-core.h"
#include <stddef.h>

typedef struct So_Align {
    struct {
        So fmt;
        size_t progress;
        size_t i0_prev;
        size_t lines_done;
    } buf;
    struct {
        size_t i0;
        size_t iNL;
        size_t iE;
        size_t n_lines;
    } config;
} So_Align;

void so_extend_al(So *out, So_Align *p, So add);
void so_fmt_al(So *out, So_Align *p, char *format, ...);

void so_al_config(So_Align *al, size_t i0, size_t iNL, size_t iE, size_t n_lines);
void so_al_rewind(So_Align *al);
void so_al_clear(So_Align *al);
void so_al_free(So_Align *al);

#define SO_ALIGN_H
#endif

