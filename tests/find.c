#include "test.h"

int main(void) {
    /* some zeros */
    EXPECT(so_find_any(SO, SO), 0);
    EXPECT(so_find_nany(SO, SO), 0);
    EXPECT(so_find_sub(SO, SO, false), 0);
    EXPECT(so_find_any(so("abcd"), SO), 4);
    EXPECT(so_find_nany(so("abcd"), SO), 0);
    EXPECT(so_find_sub(so("abcd"), SO, false), 0);
    EXPECT(so_rfind_any(SO, SO), 0);
    EXPECT(so_rfind_nany(SO, SO), 0);
    EXPECT(so_rfind_sub(SO, SO, false), 0);
    EXPECT(so_rfind_any(so("abcd"), SO), 4);
    EXPECT(so_rfind_nany(so("abcd"), SO), 4);
    EXPECT(so_rfind_sub(so("abcd"), SO, false), 0);
    /* actual finds */
    EXPECT(so_find_ch(so("abcd"), 'c'), 2);
    EXPECT(so_find_nch(so("abcd"), 'a'), 1);
    EXPECT(so_find_any(so("abcd"), so("cb")), 1);
    EXPECT(so_find_nany(so("abcd"), so("ba")), 2);
    EXPECT(so_find_ws(so("ab cd")), 2);
    EXPECT(so_find_nws(so("  abcd")), 2);
    EXPECT(so_rfind_ch(so("abcd"), 'c'), 2);
    EXPECT(so_rfind_nch(so("abcd"), 'd'), 3);
    EXPECT(so_rfind_any(so("abcd"), so("cb")), 2);
    EXPECT(so_rfind_nany(so("abcd"), so("dc")), 2);
    EXPECT(so_rfind_ws(so("ab cd")), 2);
    EXPECT(so_rfind_nws(so("abcd  ")), 4);
    EXPECT(so_find_sub(so("README.md"), so("me"), true), 4);
    EXPECT(so_find_sub(so("abcbcd"), so("bc"), false), 1);
    EXPECT(so_find_sub(so("abcbcd"), so("x"), false), 6);
    EXPECT(so_rfind_sub(so("abcbcd"), so("bc"), false), 3);
    EXPECT(so_rfind_sub(so("abbbbcd"), so("bbbb"), false), 1);
    EXPECT(so_rfind_sub(so("abcbcd"), so("x"), false), 6);
    return 0;
}

