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
    return 0;
}
