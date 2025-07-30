#include "so.h"
#include "so-as.h"
#include "so-env.h"
#include <stdlib.h>

#define SO_ENV_STACK_MAX    4096

So so_env_get(So so) {
    char *env;
    if(so.len < SO_ENV_STACK_MAX) {
        char q[SO_ENV_STACK_MAX];
        so_as_cstr(so, q, SO_ENV_STACK_MAX);
        env = getenv(q);
    } else {
        char *q = malloc(so.len + 1);
        so_as_cstr(so, q, so.len + 1);
        env = getenv(q);
        free(q);
    }
    return so_l(env);
}

