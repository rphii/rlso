#include "so-hash.h"
#include <rlc/err.h>
#include <rlc/platform-detect.h>

size_t so_hash(const So str) { /*{{{*/
    /* FNV-1a */
    /* TODO check if we are actually on 64 bit */
    char *c = so_it0(str);
    char *e = so_itE(str);
    size_t hash = 0xcbf29ce484222325;
    while(c < e) {
        hash ^= (*c)++;
        hash *= 0x00000100000001b3;
    }
    return hash;
} /*}}}*/

size_t so_hash_p(const So *str) { /*{{{*/
    ASSERT_ARG(str);
    return so_hash(*str);
}

