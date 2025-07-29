#include "test.h"

int main(void) {
    size_t z;
    EXPECT(so_as_size(so("0"), &z, 10), 0);
    EXPECT(z, 0);
    EXPECT(so_as_size(so("0"), &z, 0), 0);
    EXPECT(z, 0);
    EXPECT(so_as_size(so("00"), &z, 0), 0);
    EXPECT(z, 0);
    /* decimals */
    EXPECT(so_as_size(so("10"), &z, 10), 0);
    EXPECT(z, 10);
    EXPECT(so_as_size(so("12345"), &z, 10), 0);
    EXPECT(z, 12345);
    /* binary */
    EXPECT(so_as_size(so("0b101010"), &z, 0), 0);
    EXPECT(z, 42);
    EXPECT(so_as_size(so("0b101010"), &z, 2), 0);
    EXPECT(z, 42);
    EXPECT(so_as_size(so("101010"), &z, 2), 0);
    EXPECT(z, 42);
    EXPECT(so_as_size(so("000101010"), &z, 2), 0);
    EXPECT(z, 42);
    /* octal */
    EXPECT(so_as_size(so("012345"), &z, 0), 0);
    EXPECT(z, 012345);
    EXPECT(so_as_size(so("012345"), &z, 8), 0);
    EXPECT(z, 012345);
    EXPECT(so_as_size(so("0012345"), &z, 8), 0);
    EXPECT(z, 012345);
    EXPECT(so_as_size(so("0012345"), &z, 0), 0);
    EXPECT(z, 012345);
    /* hex */
    EXPECT(so_as_size(so("0x12345"), &z, 0), 0);
    EXPECT(z, 0x12345);
    EXPECT(so_as_size(so("0x12345"), &z, 16), 0);
    EXPECT(z, 0x12345);
    /* base 36 */
    EXPECT(so_as_size(so("z"), &z, 36), 0);
    EXPECT(z, 35);
    EXPECT(so_as_size(so("xyz"), &z, 36), 0);
    EXPECT(z, 44027);
    /* fails */
    NEXPECT(so_as_size(so("0"), &z, 37), 0);
    NEXPECT(so_as_size(so("0x"), &z, 10), 0);
    NEXPECT(so_as_size(so("x"), &z, 10), 0);
    NEXPECT(so_as_size(so("1 2"), &z, 10), 0);
    NEXPECT(so_as_size(so("-123"), &z, 10), 0);
    NEXPECT(so_as_size(so("1000000000000000000000000"), &z, 10), 1);
    EXPECT(z, SIZE_MAX);
}

