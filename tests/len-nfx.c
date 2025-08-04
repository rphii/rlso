#include "test.h"

int main(void) {
    EXPECT(so_len_nfx(SO), 0);
    EXPECT(so_len_nfx(so("")), 0);
    EXPECT(so_len_nfx(so_l(F("", BOLD))), 0);
    EXPECT(so_len_nfx(so_l("a" F("b", BOLD IT UL FG_RD BG_BK_B) "c")), 3);
    EXPECT(so_len_nfx(so_l(F("b", BOLD IT UL FG_RD BG_BK_B) F("b", BOLD IT UL FG_RD BG_BK_B) F("b", BOLD IT UL FG_RD BG_BK_B))), 3);
    EXPECT(so_len_nfx(so_l(F("abc", BOLD IT UL FG_RD BG_BK_B) F("def", BOLD IT UL FG_RD BG_BK_B) F("ghi", BOLD IT UL FG_RD BG_BK_B))), 9);
    return 0;
}

