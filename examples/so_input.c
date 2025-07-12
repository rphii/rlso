#include "../src/so.h"
#include "../src/so-input.h"
#include <stdio.h>

int main(void) {
    So user = so("User input = ");
    printf("Enter string: ");
    so_input(&user);
    printf("%.*s\n", SO_F(user));
    return 0;
}

