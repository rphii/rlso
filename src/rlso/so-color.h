#ifndef SO_COLOR_H

#include <rlc.h>

typedef enum {
    SO_COLOR_R = 0x1,
    SO_COLOR_G = 0x2,
    SO_COLOR_B = 0x4,
    SO_COLOR_A = 0x8,
    SO_COLOR_RGB = SO_COLOR_R|SO_COLOR_G|SO_COLOR_B,
    SO_COLOR_RGBA = SO_COLOR_RGB|SO_COLOR_A,
    SO_COLOR_HEX = 0x10,
    SO_COLOR_PAREN = 0x20,
    SO_COLOR_NOFX = 0x40,
    SO_COLOR_DEC = SO_COLOR_PAREN,
} So_Color_Attr;

typedef struct So So;

ErrDecl so_as_color(So so, Color *out);
void so_fmt_color(So *so, Color in, So_Color_Attr attr);

#define SO_COLOR_H
#endif

