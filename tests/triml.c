#include "test.h"

int main(void) {
    So so = so_triml(so("   abc "));
    EXPECT_CMP(so, so("abc "));
    so = so_triml(so("         "));
    EXPECT_CMP(so, SO);
    return 0;
}

