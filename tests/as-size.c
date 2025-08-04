#include "test.h"

int main(void) {
    size_t z;
    ssize_t y;
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
    /*******************************************************************/
    EXPECT(so_as_ssize(so("0"), &y, 10), 0);
    EXPECT(y, 0);
    EXPECT(so_as_ssize(so("0"), &y, 0), 0);
    EXPECT(y, 0);
    EXPECT(so_as_ssize(so("00"), &y, 0), 0);
    EXPECT(y, 0);
    /* decimals */
    EXPECT(so_as_ssize(so("10"), &y, 10), 0);
    EXPECT(y, 10);
    EXPECT(so_as_ssize(so("12345"), &y, 10), 0);
    EXPECT(y, 12345);
    /* binary */
    EXPECT(so_as_ssize(so("0b101010"), &y, 0), 0);
    EXPECT(y, 42);
    EXPECT(so_as_ssize(so("0b101010"), &y, 2), 0);
    EXPECT(y, 42);
    EXPECT(so_as_ssize(so("101010"), &y, 2), 0);
    EXPECT(y, 42);
    EXPECT(so_as_ssize(so("000101010"), &y, 2), 0);
    EXPECT(y, 42);
    EXPECT(so_as_ssize(so("-000101010"), &y, 2), 0);
    EXPECT(y, -42);
    NEXPECT(so_as_ssize(so("--000101010"), &y, 2), 0);
    /* octal */
    EXPECT(so_as_ssize(so("012345"), &y, 0), 0);
    EXPECT(y, 012345);
    EXPECT(so_as_ssize(so("012345"), &y, 8), 0);
    EXPECT(y, 012345);
    EXPECT(so_as_ssize(so("0012345"), &y, 8), 0);
    EXPECT(y, 012345);
    EXPECT(so_as_ssize(so("0012345"), &y, 0), 0);
    EXPECT(y, 012345);
    /* hex */
    EXPECT(so_as_ssize(so("0x12345"), &y, 0), 0);
    EXPECT(y, 0x12345);
    EXPECT(so_as_ssize(so("0x12345"), &y, 16), 0);
    EXPECT(y, 0x12345);
    /* base 36 */
    EXPECT(so_as_ssize(so("z"), &y, 36), 0);
    EXPECT(y, 35);
    EXPECT(so_as_ssize(so("xyz"), &y, 36), 0);
    EXPECT(y, 44027);
    EXPECT(so_as_ssize(so("-xyz"), &y, 36), 0);
    EXPECT(y, -44027);
    /* fails */
    NEXPECT(so_as_ssize(so("0"), &y, 37), 0);
    NEXPECT(so_as_ssize(so("0x"), &y, 10), 0);
    NEXPECT(so_as_ssize(so("x"), &y, 10), 0);
    NEXPECT(so_as_ssize(so("1 2"), &y, 10), 0);
    EXPECT(so_as_ssize(so("-123"), &y, 10), 0);
    EXPECT(y, -123ULL);
    NEXPECT(so_as_ssize(so("1000000000000000000000000"), &y, 10), 0);
    EXPECT(y, SSIZE_MAX);
    NEXPECT(so_as_ssize(so("-1000000000000000000000000"), &y, 10), 0);
    EXPECT(y, SSIZE_MIN);
}

