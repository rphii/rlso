#include "test.h"
#include <time.h>

void rand_so(So *out, size_t len) {
    for(size_t i = 0; i < len; ++i) so_push(out, rand());
}

int main(void) {
    VSo vs = 0;
    VSo v2 = 0;
    vso_free(&vs);
    vso_clear(&vs);
    size_t n = 1024;
    size_t lenmax = 256;
    srand(time(0));
    for(size_t i = 0; i < n; ++i) {
        So so = {0};
        rand_so(&so, rand() % lenmax);
        vso_push(&vs, so);
    }
    EXPECT(array_len(vs), n);
    for(size_t i = 0; i < n; ++i) {
        array_push(v2, vso_pop(&vs));
    }
    EXPECT(array_len(vs), 0);
    EXPECT(array_len(v2), n);
    vso_clear(&vs);
    EXPECT(array_len(vs), 0);
    srand(time(0));
    for(size_t i = 0; i < n; ++i) {
        So so = {0}, pop = vso_pop(&v2);
        rand_so(&so, rand() % lenmax);
        EXPECT_CMP(pop, so);
        so_free(&so);
        so_free(&pop);
    }
    vso_free(&vs);
    vso_free(&v2);
    vso_clear(&v2);
    EXPECT(array_len(v2), 0);
    EXPECT(array_len(vs), 0);
    return 0;
}

