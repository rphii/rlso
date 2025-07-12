#include "so.h"
#include "so-input.h"
#include <stdio.h>

void so_input(So *in) {
    int c = 0;
    while((c = getchar()) != '\n' && c != EOF) {
        so_push(in, c);
    }
    fflush(stdin);
}

