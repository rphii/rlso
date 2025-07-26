//usr/bin/env tcc "$0" ../src/*.c -lrlc -run "$@" ; exit $?

#include "../src/so.h"
#include "../src/so-fx.h"
#include "../src/so-print.h"

int main(void) {
    So so = so("Lorem ipsum dolor sit amet. ");
    So out = {0};
    So_Align al = {
        .i0 = 1, .iE = 13, .iNL = 2,
    };
    So_Fx fx = {0};
    fx = (So_Fx){ .fg = COLOR_RED, .align = &al };
    so_fmt_fx(&out, fx, "%.*s", SO_F(so));
    fx = (So_Fx){ .fg = COLOR_AQUA, .align = &al };
    so_fmt_fx(&out, fx, "%.*s", SO_F(so));
    fx = (So_Fx){ .fg = COLOR_GREEN, .align = &al };
    so_fmt_fx(&out, fx, "%.*s", SO_F(so));
    so_println(out);
    so_free(&out);
    return 0;
}

