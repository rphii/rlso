#include "so.h"
#include "so-heap.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    So s = {0};

#if defined(ENDIAN_BIG)
    printf("BIG ENDIAN\n");
#else
    printf("LITTLE ENDIAN\n");
#endif

    printf("sizeof So %zu\n", sizeof(So));

    printf("heap max %zu\n", SO_HEAP_MAX);
    printf("heap bit %zu\n", SO_HEAP_BIT);

    printf("is_heap %u\n", so_is_heap(s));
    printf("is_stack %u\n", so_is_stack(s));

    s.stack.len = 1;
    printf("simulated stack %zu\n", s.ref.len);
    printf("is_stack %u\n", so_is_stack(s));
    printf("is_heap %u\n", so_is_heap(s));

    s.stack.len = 0x80;
    printf("simulated heap %zu\n", s.ref.len);
    printf("is_heap %u\n", so_is_heap(s));
    printf("is_stack %u\n", so_is_stack(s));

    s = so("hello!");
    so_print_debug(s);
    so_push(&s, 'a');
    so_print_debug(s);
    s = so("hello, world!!");
    so_print_debug(s);
    so_push(&s, 'a');
    so_print_debug(s);
    printf(" > %u\n", s.stack.len);
    so_push(&s, 'b');
    so_print_debug(s);
    printf(" > %u\n", s.stack.len);
    so_clear(&s);
    so_print_debug(s);
#if 1
    so_push(&s, 'b');
    //so_free(&s);
    so_print_debug(s);
#endif
    so_free(&s);

    So a = so("hello ");
    So b = so("world ");
    So c = {0};
    so_extend(&c, a);
    so_extend(&c, b);
    so_print_debug(c);

    so_print_debug(so_i0(c, 5));
    so_print_debug(so_iE(c, 5));
    so_print_debug(so_sub(c, 2, 6));

    so_extend(&c, c);
    so_print_debug(c);
    so_clear(&c);
    so_extend(&c, b);
    so_extend(&c, a);
    so_fmt(&c, "asdf %s", "lol");
    so_print_debug(c);

#if 0
    So append = {0};
    for(size_t i = 0; i < 4096; ++i) {
        so_push(&append, 'x');
        so_print_debug(append);
    }
#endif

    so_free(&c);
    so_print_debug(c);
    return 0;
}

