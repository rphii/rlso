#include "test.h"

int main(void) {
    So so = so_trimr(so(" abc   "));
    EXPECT_CMP(so, so(" abc"));
    so = so_trimr(so("           "));
    EXPECT_CMP(so, SO);
    return 0;
}

