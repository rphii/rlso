#include "test.h"

int main(void) {
    So in = SO;
    So out = SO;

    so_copy(&in, so("Man"));
    so_base64_fmt_encode(&out, in);
    EXPECT_CMP(out, so("TWFu"));
    so_clear(&in);
    so_printdbg(out);
    so_base64_fmt_decode(&in, out);
    so_printdbg(in);
    EXPECT_CMP(in, so("Man"));
    so_clear(&out);

    so_copy(&in, so("Ma"));
    so_base64_fmt_encode(&out, in);
    EXPECT_CMP(out, so("TWE="));
    so_clear(&in);
    so_printdbg(out);
    so_base64_fmt_decode(&in, out);
    so_printdbg(in);
    EXPECT_CMP(in, so("Ma"));
    so_clear(&out);

    so_copy(&in, so("M"));
    so_base64_fmt_encode(&out, in);
    EXPECT_CMP(out, so("TQ=="));
    so_clear(&in);
    so_printdbg(out);
    so_base64_fmt_decode(&in, out);
    so_printdbg(in);
    EXPECT_CMP(in, so("M"));
    so_clear(&out);

    so_copy(&in, so("Many hands make light work."));
    so_base64_fmt_encode(&out, in);
    EXPECT_CMP(out, so("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu"));
    so_clear(&in);
    so_printdbg(out);
    so_base64_fmt_decode(&in, out);
    so_printdbg(in);
    EXPECT_CMP(in, so("Many hands make light work."));
    so_clear(&out);

    so_free(&in);
    so_free(&out);
    return 0;
}


