#include "../src/so.h"
#include <stdio.h>

int main(void) {
    So str = so("Hello, World!");
    printf("%.*s\n", SO_F(str));
    return 0;
}

