#include "test.h"

int main(void) {
    EXPECT(so_count_ch(so("abc"), 'x'), 0);
    EXPECT(so_count_ch(so("abcxxxabc"), 'x'), 3);
    EXPECT(so_count_nch(so("abc"), 'x'), 3);
    EXPECT(so_count_nch(so("abcxxxabc"), 'x'), 6);
    EXPECT(so_count_any(so("abc"), so("ba")), 2);
    EXPECT(so_count_any(so("abcxxxabc"), so("ba")), 4);
    EXPECT(so_count_nany(so("abc"), so("ba")), 1);
    EXPECT(so_count_nany(so("abcxxxabc"), so("ba")), 5);
    EXPECT(so_count_overlapx(so("eyo"), so("eyoab"), false), 3);
    EXPECT(so_count_overlapx(so("eyoabc"), so("eyo"), false), 3);
    EXPECT(so_count_overlapx(SO, so("eyo"), false), 0);
    EXPECT(so_count_overlapx(so("asdf"), SO, false), 0);
    /* empty */
    EXPECT(so_count_ch(SO, 'x'), 0);
    EXPECT(so_count_nch(SO, 'x'), 0);
    EXPECT(so_count_any(SO, SO), 0);
    EXPECT(so_count_nany(SO, SO), 0);
    /* stacked */
    So so = SO;
    so_extend(&so, so("abcxyz"));
    NEXPECT(so_is_stack(so), 0);
    EXPECT(so_count_ch(so, 'x'), 1);
    EXPECT(so_count_nch(so, 'x'), 5);
    EXPECT(so_count_any(so, so), 6);
    EXPECT(so_count_any(so("eyo"), so), 1);
    EXPECT(so_count_nany(so("eyo"), so), 2);
    EXPECT(so_count_any(so, so("eyo")), 1);
    EXPECT(so_count_nany(so, so("eyo")), 5);
    return 0;
}

