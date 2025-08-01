#include "../src/so.h"
#include "../src/so-heap.h"
#include "../src/so-print.h"
#include "../src/so-splice.h"
#include "../src/so-trim.h"
#include "../src/so-uc.h"
#include "../src/so-input.h"
#include "../src/so-fx.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int err = 0;
    So s = {0};

#if 0
    So onebuf = {0};
    size_t oneindex = 0;
    so_fmt(&onebuf, "hello this is some sample string");
    so_1buf_old(&onebuf, &oneindex);
    printf("1INPUT:");
    so_input(&onebuf);
    so_1buf_new(&onebuf, &oneindex);
    printf("ONEBUF:");
    so_println(onebuf);
    so_free(&onebuf);
#endif

#if defined(ENDIAN_BIG)
    printf("BIG ENDIAN\n");
#else
    printf("LITTLE ENDIAN\n");
#endif

    printf("sizeof So %zu\n", sizeof(So));

    printf("is_heap %u\n", so_is_heap(s));

    s = so("hello!");
    so_printdbg(s);
    so_push(&s, 'a');
    so_printdbg(s);
    s = so("hello, world!");
    so_printdbg(s);
    so_push(&s, '?');
    so_printdbg(s);
    so_push(&s, 'a');
    so_printdbg(s);
    //printf(" > %u\n", s.stack.len);
    so_push(&s, 'b');
    so_printdbg(s);
    //printf(" > %u\n", s.stack.len);
    so_push(&s, 'c');
    so_printdbg(s);
    so_clear(&s);
    so_printdbg(s);
#if 1
    so_push(&s, 'b');
    //so_free(&s);
    so_printdbg(s);
#endif
    so_free(&s);

    So a = so("hello ");
    So b = so("world ");
    So c = {0};
    so_extend(&c, a);
    so_extend(&c, b);
    so_printdbg(c);

    so_printdbg(so_i0(c, 5));
    so_printdbg(so_iE(c, 5));
    so_printdbg(so_sub(c, 2, 6));

    so_extend(&c, c);
    so_printdbg(c);
    so_clear(&c);
    so_extend(&c, b);
    so_extend(&c, a);
    so_fmt(&c, "asdf %s", "lol");
    so_printdbg(c);

    for(So splice = {0}; so_splice(so("a0,   b11,c222  ,,        d4444        , "), &splice, ','); ) {
        splice = so_trim(splice);
        if(so_is_empty(splice)) continue;
        so_println(splice);
        so_println(so_triml(splice));
        so_println(so_trimr(splice));
        so_println(so_trim(splice));
    }

    So_Uc_Point point = { .val = 0x2235 };
    So uc = {0};
    err = so_uc_fmt_point(&uc, &point);
    so_println(uc);
    so_uc_point(uc, &point);
    printf("point %u / %#x, bytes: %u\n", point.val, point.val, point.bytes);

#if 0
    So append = {0};
    for(size_t i = 0; i < 4096; ++i) {
        so_push(&append, 'x');
        so_printdbg(append);
    }
#endif

    So_Align al = {
        .i0 = 1,
        .iNL = 2,
        .iE = 10,
    };
    So_Fx fx = {
        .bold = true,
        .italic = true,
        .underline = true,
        .align = &al,
    };
    So sfx = {0};
    so_fmt_fx(&sfx, fx, "a string with a very long text attached to it that is basically unnecessary!\n");
    so_print(sfx);
    so_free(&sfx);

    so_free(&c);
    so_printdbg(c);
    return 0;
}

