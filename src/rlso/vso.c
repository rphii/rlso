#include <rlc.h>
#include <stdlib.h>
#include "vso.h"

void vso_push(VSo *v, So so) {
    ASSERT_ARG(v);
    array_push(*v, so);
}

So vso_pop(VSo *v) {
    ASSERT_ARG(v);
    ASSERT_ARG(*v);
    return array_pop(*v);
}

void vso_free(VSo *v) {
    ASSERT_ARG(v);
    if(!*v) return;
    array_free_set(*v, so_free);
    array_free(*v);
}

void vso_clear(VSo *v) {
    ASSERT_ARG(v);
    if(!*v) return;
    array_clear(*v);
}


