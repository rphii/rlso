#include <stdio.h>
#include <rphii/so.h>

int main(void) {
    char *cstr = "Hello, World!";
    So str = so_l(cstr);
    printf("%.*s\n", SO_F(str));
    return 0;
}
