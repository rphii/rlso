#include "test.h"

int unescape(So buf, So cmp) {
    So unescaped = SO;
    int result = so_fmt_unescape(&unescaped, buf, 0);
    printff("COMPARE: (result %u)",result);
    so_printdbg(unescaped);
    so_printdbg(cmp);
    if(!result) result = so_cmp(unescaped, cmp);
    so_free(&unescaped);
    printff("  result: %u",result);
    return result;
}

int unescape_fail(So buf, size_t i) {
    int result = 0;
    So unescaped = SO;
    size_t i_err = so_fmt_unescape(&unescaped, buf, 0);
    printff("ERR? %zu == %zu", i_err, i);
    so_printdbg(unescaped);
    if(!i_err) {
        result = 1;
    } else if(i != i_err) {
        result = 1;
    }
    so_free(&unescaped);
    printff("  result: %u",result);
    return result;
}

int main(void) {

    int result = 0;

    result |= unescape(so("\\a"), so("\a"));
    result |= unescape(so("\\b"), so("\b"));
    result |= unescape(so("\\f"), so("\f"));
    result |= unescape(so("\\n"), so("\n"));
    result |= unescape(so("\\r"), so("\r"));
    result |= unescape(so("\\t"), so("\t"));
    result |= unescape(so("\\v"), so("\v"));
    result |= unescape(so("\\\\"), so("\\"));
    result |= unescape(so("\\\'"), so("\'"));
    result |= unescape(so("\\\""), so("\""));
    result |= unescape(so("\\e"), so("\033"));

    result |= unescape(so("X\\aX\\bX\\fX\\nX\\rX\\tX\\vX\\\\X\\'X\\\"X\\?X"), so("X\aX\bX\fX\nX\rX\tX\vX\\X'X\"X?X"));

    result |= unescape(so("\\o123"), so("83"));
    result |= unescape(so("\\x42"), so("66"));
    result |= unescape(so("\\x4242"), so("16962"));
    result |= unescape(so(" \\u03C6 "), so(" φ "));
    result |= unescape(so(" \\u03c6 "), so(" φ "));
    result |= unescape(so(" \\U00011D60 "), so(" 𑵠 "));

    result |= unescape_fail(so("\\x"), 1);
    result |= unescape_fail(so("\\x!"), 2);
    result |= unescape_fail(so("  \\x"), 3);
    result |= unescape_fail(so("  \\x!"), 4);

    result |= unescape_fail(so("\\o"), 1);
    result |= unescape_fail(so("\\o7"), 2);
    result |= unescape_fail(so("\\o7  "), 2);
    result |= unescape_fail(so("\\o67  "), 3);
    result |= unescape_fail(so("\\o657  "), 4);

    result |= unescape_fail(so("\\u"), 1);
    result |= unescape_fail(so("\\u1"), 2);
    result |= unescape_fail(so("\\u12"), 3);
    result |= unescape_fail(so("\\u123"), 4);

    result |= unescape_fail(so("\\U"), 1);
    result |= unescape_fail(so("\\U1"), 2);
    result |= unescape_fail(so("\\U12"), 3);
    result |= unescape_fail(so("\\U123"), 4);
    result |= unescape_fail(so("\\U1234"), 5);
    result |= unescape_fail(so("\\U12345"), 6);
    result |= unescape_fail(so("\\U123456"), 7);
    result |= unescape_fail(so("\\U1234567"), 8);

    result |= unescape_fail(so("\\D"), 1);
    result |= unescape_fail(so(" \\D"), 2);

    So tmp = SO;
    so_clear(&tmp);
    result |= so_fmt_unescape(&tmp, so("'"), '\'');
    so_printdbg(tmp);
    EXPECT_CMP(tmp, so(""));

    so_clear(&tmp);
    result |= so_fmt_unescape(&tmp, so("a'"), '\'');
    so_printdbg(tmp);
    EXPECT_CMP(tmp, so("a"));

    so_clear(&tmp);
    result |= so_fmt_unescape(&tmp, so("asdf]lol"), ']');
    so_printdbg(tmp);
    EXPECT_CMP(tmp, so("asdf"));

    so_clear(&tmp);
    result |= (so_fmt_unescape(&tmp, so("[asdf["), ']') != -1);
    so_printdbg(tmp);
    EXPECT_CMP(tmp, so(""));

    so_clear(&tmp);
    result |= (so_fmt_unescape(&tmp, so("[asdf["), ']') != -1);
    so_printdbg(tmp);
    EXPECT_CMP(tmp, so(""));
    
    so_free(&tmp);

    printff("FINAL RESULT %u", result);
    return result;
}

