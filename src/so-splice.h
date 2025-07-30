#ifndef SO_SPLICE_H

typedef struct So So;
typedef struct So_Ref So_Ref;

#include <stddef.h>

size_t so_splice(So to_splice, So *prev, char sep);

#define SO_SPLICE_H
#endif

