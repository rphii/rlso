#include "../src/rlso.h"

#include <stdio.h>

int main(void) {

#if 1
    So_Switch s[] = {
        So_Switch_Pair(1, so("asd")),
        So_Switch_Pair(2, so("xyz")),
    };
#endif

    int r = so_switch(so("asd"), s);

#if 0
    int r2 = so_switch(so("asd"), So_Switches(
            So_Switch_Pair(1, so("a")),
            So_Switch_Pair(1, so("b")),
            ));
#endif

    switch(r) {
        case 1: {
            printff("OK");
        } break;
        default:
            printff("FAIL");
            return -1;
    }

    //So_Switch *s[] = SO_SWITCH({1, so("lol")});


    return 0;
}

