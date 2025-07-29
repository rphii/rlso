#include "test.h"

int main(void) {
    So so = so_trim(so(" abc   "));
    EXPECT_CMP(so, so("abc"));
    so = so_trim(so(" abc"));
    EXPECT_CMP(so, so("abc"));
    so = so_trim(so("abc"));
    EXPECT_CMP(so, so("abc"));
    so = so_trim(SO);
    EXPECT_CMP(so, SO);
    return 0;
}


