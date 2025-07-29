#include "test.h"

int main(void) {
    size_t z;
    EXPECT(so_as_size(so("0"), &z, 10), 0);
    EXPECT(z, 0);
    EXPECT(so_as_size(so("10"), &z, 10), 0);
    EXPECT(z, 10);
    /* fails */
    NEXPECT(so_as_size(so("0x"), &z, 10), 0);
    NEXPECT(so_as_size(so("x"), &z, 10), 0);
    NEXPECT(so_as_size(so("1 2"), &z, 10), 0);
    NEXPECT(so_as_size(so("-123"), &z, 10), 0);
    EXPECT(z, 0);
    NEXPECT(so_as_size(so("1000000000000000000000000"), &z, 10), 1);
    EXPECT(z, SIZE_MAX);
}

