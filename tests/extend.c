#include "test.h"

int main(void) {
    So so = so("abcdefghijklmnopqrstuvwxyz");
    for(size_t i = 0; i < 0x8; ++i) {
        so_extend(&so, so);
    }
    char c = 'a';
    for(size_t i = 0; i < so_len(so); ++i) {
        EXPECT(so_at(so, i), c);
        c = (c + 1 - 'a') % ('z' - 'a' + 1) + 'a';
    }
    so_free(&so);
    return 0;
}

