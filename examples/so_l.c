#include "../src/so.h"
#include <stdio.h>

int main(void) {
    char *cstr = "Hello, World!";
    So str = so_l(cstr);
    printf("%.*s\n", SO_F(str));
    return 0;
}
