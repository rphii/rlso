#ifndef SO_FX_H

#include <stdbool.h>
#include <stddef.h>
#include <rl/color.h>

#include "so-align.h"

typedef struct So So;

typedef struct So_Fx {
    So_Align *align;
    Color fg;
    Color bg;
    bool *nocolor;
    bool bold;
    bool italic;
    bool underline;
    bool bashsafe;
} So_Fx;

size_t so_len_nfx(So str);
size_t so_nfx_index(So so, size_t index);
void so_fmt_fx(So *out, So_Fx fx, char *fmt, ...);
void so_fmt_fgbgx(So *out, Color fg, Color bg, bool bold, bool italic, bool underline, bool bashsafe, char *fmt, ...);

#define SO_FX_H
#endif

