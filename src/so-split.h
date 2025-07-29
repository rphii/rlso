#ifndef SO_SPLIT_H

#include <stddef.h>
#include "so-cmp-attr.h"

typedef struct So So;
typedef struct So_Ref So_Ref;

#define so_split(so, i, right) _so_split(so_ref((so)), i, right)
#define so_split_ext(so, i, n, right) _so_split_ext(so_ref((so)), i, n, right)

#define so_split_ch(so, c, right) _so_split_ch(so_ref((so)), c, right)
#define so_split_nch(so, c, right) _so_split_nch(so_ref((so)), c, right)
#define so_split_sub(so, sub, right, attr) _so_split_sub()
#define so_split_nsub(so, sub, right, attr) _so_split_nsub()

#define so_rsplit_ch(so, c, right) _so_rsplit_ch(so_ref((so)), c, right)
#define so_rsplit_nch(so, c, right) _so_rsplit_nch(so_ref((so)), c, right)
#define so_rsplit_sub(so, sub, right, attr) _so_rsplit_sub(so_ref((so)), sub, right, attr)
#define so_rsplit_nsub(so, sub, right, attr) _so_rsplit_nsub(so_ref((so)), sub, right, attr)

So _so_split(So_Ref ref, size_t i, So *right);
So _so_split_ext(So_Ref ref, size_t i, size_t n, So *right);

So _so_split_ch(So_Ref ref, char c, So *right);
So _so_split_nch(So_Ref ref, char c, So *right);
So _so_split_sub(So_Ref ref, So sub, So *right, So_Cmp_Attr attr);
So _so_split_nsub(So_Ref ref, So sub, So *right, So_Cmp_Attr attr);

So _so_rsplit_ch(So_Ref ref, char c, So *right);
So _so_rsplit_nch(So_Ref ref, char c, So *right);
So _so_rsplit_sub(So_Ref ref, So sub, So *right, So_Cmp_Attr attr);
So _so_rsplit_nsub(So_Ref ref, So sub, So *right, So_Cmp_Attr attr);

#define SO_SPLIT_H
#endif

