#ifndef SO_SPLICE_H

typedef struct So So;
typedef struct So_Ref So_Ref;

#include <stddef.h>

#define so_splice(to_splice, prev, sep) \
    _so_splice(so_ref((to_splice)), prev, sep)
size_t _so_splice(So_Ref to_splice, So *prev, char sep);

#define SO_SPLICE_H
#endif

