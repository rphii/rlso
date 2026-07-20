#include "test.h"

int main(void) {
    So right;
    EXPECT_CMP(so_get_ext(so("abc.png")), so(".png"));
    return 0;
}


