#ifndef SO_ENV_H

typedef struct So So;

#include <stdbool.h>

int so_env_get(So *out, So so);
void so_extend_wordexp(So *out, So path, bool only_if_exists);

#define SO_ENV_H
#endif

