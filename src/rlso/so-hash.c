#include "so-hash.h"
#include <rl/err.h>

size_t so_hash(const So str) { /*{{{*/
    size_t hash = 5381;
    size_t i = 0;
    while(i < so_len(str)) {
        unsigned char c = str.str[i++];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
} /*}}}*/

size_t so_hash_p(const So *str) { /*{{{*/
    ASSERT_ARG(str);
    return so_hash(*str);
}

