#ifndef SO_SPLIT_H

#include <stddef.h>
#include "so-cmp-attr.h"

typedef struct So So;

So so_split(So so, size_t i, So *right);
So so_split_ext(So so, size_t i, size_t n, So *right);

So so_split_ch(So so, char c, So *right);
So so_split_nch(So so, char c, So *right);
So so_split_sub(So so, So sub, So *right, So_Cmp_Attr attr);
So so_split_nsub(So so, So sub, So *right, So_Cmp_Attr attr);

So so_rsplit_ch(So so, char c, So *right);
So so_rsplit_nch(So so, char c, So *right);
So so_rsplit_sub(So so, So sub, So *right, So_Cmp_Attr attr);
So so_rsplit_nsub(So so, So sub, So *right, So_Cmp_Attr attr);

#define SO_SPLIT_H
#endif

