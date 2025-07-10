#include "so.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    So s = {0};

#if defined(ENDIAN_BIG)
    printf("BIG ENDIAN\n");
#else
    printf("LITTLE ENDIAN\n");
#endif

    printf("stack thresh %zu\n", SO_STACK_THRESH);
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

    so_extend(&c, c);
    so_print_debug(c);
    so_clear(&c);
    so_extend(&c, b);
    so_extend(&c, a);
    so_print_debug(c);

    so_free(&c);
    so_print_debug(c);
    return 0;
}

