#ifndef SO_AS_H

#include <stddef.h>
#include <rl/err.h>

typedef struct So So;

void so_as_cstr(So so, char *cstr, size_t cap);
ErrDecl so_as_size(So so, size_t *out, int base);

#define SO_AS_H
#endif

