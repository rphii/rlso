#include "test.h"

int main(void) {
    So in = SO, splice = SO;
    while(so_splice(in, &splice, '\n')) {
        printff("invisible text");
    }
    so_free(&in);
}


