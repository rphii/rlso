#include "so-core.h"
#include "so-as.h"
#include "so-env.h"
#include <stdlib.h>
#include <wordexp.h>
#include <unistd.h>

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

void so_extend_wordexp(So *out, So path, bool only_if_exists) {
    char *clean = so_dup(path); /* TODO create a str_copy_ro .. read-only copy, where it doesn't extend if end == len ... */
    wordexp_t word = {0};
    if(wordexp(clean, &word, 0)) {
        goto defer;
    }
    if(!word.we_wordv[0]) {
        goto defer;
    }
    char *result = word.we_wordv[0];
    if(only_if_exists && (!strlen(result) || access(result, R_OK) == -1)) {
        goto defer;
    }
    so_extend(out, so_l(result));
defer:
    free(clean);
    wordfree(&word);
}

