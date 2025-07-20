#include <rphii/err.h>
#include <rphii/array.h>
#include <stdlib.h>
#include "vso.h"

void vso_push(Vso *v, So so) {
    ASSERT_ARG(v);
    array_push(*v, so);
}

So vso_pop(Vso *v) {
    ASSERT_ARG(v);
    return array_pop(*v);
}

void vso_free(Vso *v) {
    ASSERT_ARG(v);
    array_free_set(*v, sizeof(So), (ArrayFree)so_free);
    array_free(*v);
}


