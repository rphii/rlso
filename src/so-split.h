#ifndef SO_SPLIT_H

typedef struct So So;

So so_split_ch(So so, char c, So *right);
So so_split_nch(So so, char c, So *right);
So so_split_sub(So so, So sub, So *right);
So so_split_nsub(So so, So sub, So *right);

So so_rsplit_ch(So so, char c, So *right);
So so_rsplit_nch(So so, char c, So *right);
So so_rsplit_sub(So so, So sub, So *right);
So so_rsplit_nsub(So so, So sub, So *right);

#define SO_SPLIT_H
#endif

