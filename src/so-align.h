#ifndef SO_ALIGN_H

#include "so.h"
#include <stddef.h>

typedef struct So_Align {
    size_t progress;
    size_t i0_prev;
    So fmt;
    size_t i0;
    size_t iNL;
    size_t iE;
} So_Align;

void so_fmt_al(So *out, So_Align *p, char *format, ...);

#define SO_ALIGN_H
#endif

