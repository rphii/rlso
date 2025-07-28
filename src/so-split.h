#ifndef SO_SPLIT_H

#include <stddef.h>
#include "so-cmp-attr.h"

typedef struct So So;

#define so_split(so, i, right) _so_split(&(so), i, right)
#define so_split_ext(so, i, n, right) _so_split_ext(&(so), i, n, right)

#define so_split_ch(so, c, right) _so_split_ch(&(so), c, right)
#define so_split_nch(so, c, right) _so_split_nch(&(so), c, right)
#define so_split_sub(so, sub, right, attr) _so_split_sub()
#define so_split_nsub(so, sub, right, attr) _so_split_nsub()

#define so_rsplit_ch(so, c, right) _so_rsplit_ch(&(so), c, right)
#define so_rsplit_nch(so, c, right) _so_rsplit_nch(&(so), c, right)
#define so_rsplit_sub(so, sub, right, attr) _so_rsplit_sub(&(so), sub, right, attr)
#define so_rsplit_nsub(so, sub, right, attr) _so_rsplit_nsub(&(so), sub, right, attr)

So _so_split(So *so, size_t i, So *right);
So _so_split_ext(So *so, size_t i, size_t n, So *right);

So _so_split_ch(So *so, char c, So *right);
So _so_split_nch(So *so, char c, So *right);
So _so_split_sub(So *so, So sub, So *right, So_Cmp_Attr attr);
So _so_split_nsub(So *so, So sub, So *right, So_Cmp_Attr attr);

So _so_rsplit_ch(So *so, char c, So *right);
So _so_rsplit_nch(So *so, char c, So *right);
So _so_rsplit_sub(So *so, So sub, So *right, So_Cmp_Attr attr);
So _so_rsplit_nsub(So *so, So sub, So *right, So_Cmp_Attr attr);

#define SO_SPLIT_H
#endif

