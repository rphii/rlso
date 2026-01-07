#include <rlc.h>
#include <stdlib.h>
#include "vso.h"

inline void vso_push(VSo *v, So so) {
    ASSERT_ARG(v);
    array_push(*v, so);
}

inline So vso_pop(VSo *v) {
    ASSERT_ARG(v);
    ASSERT_ARG(*v);
    return array_pop(*v);
}

inline void vso_free(VSo *v) {
    ASSERT_ARG(v);
    if(!*v) return;
    array_free_ext(*v, so_free);
    array_free(*v);
}

inline void vso_clear(VSo *v) {
    ASSERT_ARG(v);
    if(!*v) return;
    array_clear(*v);
}


