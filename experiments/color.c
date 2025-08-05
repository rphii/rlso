#include "../src/so.h"

int main(void) {
    //So so = so("rgba(0xff, 0xf1, 0x21, 0x64)");
    //So so = so("abgr(0x64, 0x21, 0xf1, 0xff)");
    //So so = so("agbr(0x64, 0xf1, 0x21, 0xff)");
    //So so = so("wa(0x64, 34)");
    //So so = so("aw(34, 0x64)");
    //So so = so("bg(94, 64)");
    //So so = so("bg(9464)");
    //So so = so("wa(0xff,0xff)");
    So so = so("aw(0f7f)");
    //So so = so("rgb   (      0xff , 0xf1\t, 0x21          )");
    //So so = so("#fff121fa");
    So out = SO;
    Color col = COLOR_NONE;
    if(so_as_color(so, &col)) ABORT("invalid format");
    so_fmt_color(&out, col, SO_COLOR_RGBA|SO_COLOR_DEC);
    so_println(out);
    so_free(&out);
    return 0;
}

