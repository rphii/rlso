#ifndef SO_UC_H

#include <rl/err.h>
#include <stdint.h>

typedef struct So So;

typedef struct So_Uc_Point {
    uint32_t val;
    int bytes;
} So_Uc_Point;

ErrDecl so_uc_point(So in, So_Uc_Point *point);
ErrDecl so_uc_fmt_point(So *out, So_Uc_Point *point);

#define SO_UC_H
#endif

