#ifndef SO_ENV_H

typedef struct So So;

#include <stdbool.h>

So so_env_get(So so);
void so_extend_wordexp(So *out, So path, bool only_if_exists);

#define SO_ENV_H
#endif

