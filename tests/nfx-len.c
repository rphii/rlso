#include "test.h"

int main(void) {
    EXPECT(so_len_nfx(SO), 0);
    EXPECT(so_len_nfx(so("")), 0);
    EXPECT(so_len_nfx(so_l("")), 0);
    EXPECT(so_len_nfx(so_l(F("", BOLD))), 0);
    EXPECT(so_len_nfx(so_l("a" F("b", BOLD) "c")), 3);
    EXPECT(so_len_nfx(so_l(F("", BOLD) F("", IT))), 0);
    return 0;
}

