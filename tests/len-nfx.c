#include "test.h"

int main(void) {
    EXPECT(so_len_nfx(SO), 0);
    EXPECT(so_len_nfx(so("")), 0);
    EXPECT(so_len_nfx(so_l(F("", BOLD))), 0);
    EXPECT(so_len_nfx(so_l("a" F("b", BOLD IT UL FG_RD BG_BK_B) "c")), 3);
    return 0;
}

