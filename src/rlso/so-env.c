#include "so-core.h"
#include "so-as.h"
#include "so-env.h"
#include <stdlib.h>
#include <wordexp.h>
#include <unistd.h>

#define SO_ENV_STACK_MAX    4096

int so_env_get(So *out, So so) {
    char *env = 0;
    so_free(out);
    if(so.len < SO_ENV_STACK_MAX) {
        char q[SO_ENV_STACK_MAX];
        so_as_cstr(so, q, SO_ENV_STACK_MAX);
        env = getenv(q);
    } else {
        char *q = so_dup(so);
        env = getenv(q);
        free(q);
    }
    if(!env) return -1;
    *out = so_l(env);
    return 0;
}

void so_extend_wordexp(So *out, So path, bool only_if_exists) {
    char *clean = so_dup(path); /* TODO create a str_copy_ro .. read-only copy, where it doesn't extend if end == len ... */
    wordexp_t word = {0};
    if(wordexp(clean, &word, 0)) {
        goto defer;
    }
    char *result = word.we_wordv[0];
    if(!result) {
        goto defer;
    }
    if(only_if_exists && (!strlen(result) || access(result, R_OK) == -1)) {
        goto defer;
    }
    //printff("RESULT %p",result);
    //printff("RESULS %s",result);
    //getchar();
#if 1
    so_extend(out, so_l(result));
#endif
defer:
    free(clean);
    wordfree(&word);
}

