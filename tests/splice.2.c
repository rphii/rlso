#include "test.h"

int main(void) {
    So in = so("ab, ,, de,  xy");
    so_push(&in, ' ');
    So exp[] = { so("ab"), so(""), so(""), so("de"), so("xy") };
    size_t n = 0;
    for(So splice = {0}; so_splice(in, &splice, ','); ++n) {
        if(so_is_zero(splice)) continue;
        splice = so_trim(splice);
        printf("%zu -> '%.*s' :: '%.*s'\n", n, SO_F(splice), SO_F(exp[n]));
        EXPECT(so_cmp(splice, exp[n]), 0);
    }
    EXPECT(n, 5);
    so_free(&in);
}

