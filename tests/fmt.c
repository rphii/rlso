#include "test.h"

int main(void) {
    So so = SO;
    so_fmt(&so, "%.*s", SO_F(SO));
    EXPECT(so_len(so), 0);
    EXPECT(so_len_nfx(so), 0);
    so_fmt(&so, "%c", 'a');
    EXPECT(so_len(so), 1);
    EXPECT(so_len_nfx(so), 1);
    so_fmt(&so, "%.*s", SO_F(SO));
    EXPECT(so_len(so), 1);
    so_fmt(&so, "%u", 10);
    EXPECT(so_len(so), 3);
    EXPECT(so_len_nfx(so), 3);
    so_clear(&so);
    for(size_t i = 0; i < 4096; ++i) {
        so_fmt(&so, "%c", rand());
        EXPECT(so_len(so), i + 1);
        EXPECT(so_len_nfx(so), i + 1);
    }
    so_free(&so);
    return 0;
}

