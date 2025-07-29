#include "test.h"

int main(void) {
    So in = so("abc, ,, def,  xyz ");
    So exp[] = { so("abc"), so(""), so(""), so("def"), so("xyz") };
    size_t n = 0;
    for(So splice = {0}; so_splice(in, &splice, ','); ++n) {
        if(so_is_zero(splice)) continue;
        //printf("%zu:%zu-%zu -> '%.*s' :: '%.*s'\n", n, splice.ref.str-in.ref.str,splice.ref.len, SO_F(splice), SO_F(exp[n]));
        splice = so_trim(splice);
        //printf("%zu:%zu-%zu -> '%.*s' :: '%.*s'\n", n, splice.ref.str-in.ref.str,splice.ref.len, SO_F(splice), SO_F(exp[n]));
        EXPECT(so_cmp(splice, exp[n]), 0);
    }
    EXPECT(n, 5);
}

