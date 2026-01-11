#include "../src/rlso.h"

#include <stdio.h>

int main(void) {

    So input = so("asd");

    int r = so_switch(input, -1, So_Switches(
                1, so("asd"),
                2, so("xyz"),
                ));

    switch(r) {

        case 1: {
            printff("OK");
        } break;

        default: {
            printff("FAIL");
            return -1;
        } break;

    }


    return 0;
}

