#include "test.h"

int main(void) {
    So right;
    EXPECT_CMP(so_split(SO, 0, &right), SO);
    EXPECT_CMP(right, SO);
    EXPECT_CMP(so_split(so("abcd"), 2, &right), so("ab"));
    EXPECT_CMP(right, so("cd"));
    EXPECT_CMP(so_split_nch(so("xxxabc"), 'x', &right), so("xxx"));
    EXPECT_CMP(right, so("abc"));
    EXPECT_CMP(so_rsplit_nch(so("abcxxx"), 'x', &right), so("abc"));
    EXPECT_CMP(right, so("xxx"));
    EXPECT_CMP(so_split_sub(so("abca-stringa-stringxxx"), so("a-string"), &right, SO_CMP), so("abc"));
    EXPECT_CMP(right, so("a-stringxxx"));
    So r,l=so_rsplit_sub(so("abca-stringa-stringxx"),so("a-string"),&r,false);
    printff("RIGHT");
    so_println(r);
    printff("LEFT");
    so_println(l);
    EXPECT_CMP(so_rsplit_sub(so("abca-stringa-stringxxx"), so("a-string"), &right, SO_CMP), so("abca-string"));
    EXPECT_CMP(right, so("xxx"));
    return 0;
}
