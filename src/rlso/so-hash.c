#include "so-hash.h"
#include <rlc/err.h>
#include <rlc/platform-detect.h>

size_t so_hash(const So str) { /*{{{*/
    /* FNV1-a */
    /* TODO check if we are actually on 64 bit */
    size_t i = 0;
    size_t hash = 0xcbf29ce484222325;
    while(i < so_len(str)) {
        unsigned char c = str.str[i++];
        hash *= 0x00000100000001b3;
        hash ^= c;
    }
    return hash;
} /*}}}*/

size_t so_hash_p(const So *str) { /*{{{*/
    ASSERT_ARG(str);
    return so_hash(*str);
}

