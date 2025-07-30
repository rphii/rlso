#include "test.h"
int main(void) {
    So so = so(0);
    So clone = {0};
    So copy = {0};
    So r = {0};
    EXPECT(so_is_empty(so), true);
    EXPECT(so_is_empty(r), true);
    EXPECT(so_len(so), 0);
    char first;
    for(size_t i = 0; i < 4096; ++i) {
        char c = rand() % ('z' - 'A') + 'A';
        if(!i) first = c;
        so_copy(&copy, so);
        /* so */
        so_push(&so, c);
        EXPECT(so_len(so), i + 1);
        EXPECT(so_at(so, i), c);
        EXPECT(so_is_empty(so), false);
        EXPECT(so_at0(so), first);
        /* ref */
        r = so_ll(so_it0(so), i);
        clone = so_clone(r);
        so_push(&r, c);
        EXPECT(so_len(r), i + 1);
        EXPECT(so_at(r, i), c);
        EXPECT(so_is_empty(r), false);
        EXPECT(so_at0(r), first);
        /* clone */
        EXPECT(so_len(clone), i);
        so_push(&clone, c);
        EXPECT(so_len(clone), i + 1);
        EXPECT(so_at(clone, i), c);
        EXPECT(so_is_empty(clone), false);
        EXPECT(so_at0(clone), first);
        /* copy */
        EXPECT(so_len(copy), i);
        so_push(&copy, c);
        EXPECT(so_len(copy), i + 1);
        EXPECT(so_at(copy, i), c);
        EXPECT(so_is_empty(copy), false);
        EXPECT(so_at0(copy), first);
        /* clean */
        so_free(&clone);
        so_free(&r);
        so_clear(&copy);
    }
    so_free(&copy);
    so_free(&so);
    return 0;
}

