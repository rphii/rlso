#include "test.h"

int main(void) {
    So so = {0};
    so_fmt_fgbgx(&so, COLOR_NONE, COLOR_NONE, false, false, false, false, "%.*s", SO_F(SO));
    EXPECT(so_len_nfx(so), 0);
    so_fmt_fgbgx(&so, COLOR_NONE, COLOR_NONE, false, false, false, false, "%.*s", SO_F(SO));
    EXPECT(so_len_nfx(so), 0);
    so_fmt_fgbgx(&so, COLOR_NONE, COLOR_NONE, false, false, false, false, "%c", 'a');
    EXPECT(so_len_nfx(so), 1);
    so_fmt_fgbgx(&so, COLOR_NONE, COLOR_NONE, false, false, false, false, "%.*s", SO_F(SO));
    EXPECT(so_len_nfx(so), 1);
    so_fmt_fgbgx(&so, COLOR_NONE, COLOR_NONE, false, false, false, false, "%u", 10);
    so_printdbg(so);
    EXPECT(so_len_nfx(so), 3);
    so_free(&so);
    return 0;
}

