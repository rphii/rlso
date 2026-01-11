#include "so-switch.h"
#include "so-cmp.h"

int so_switch(So input, So_Switches cases) {
    for(size_t i = 0; i < cases.len; ++i) {
        if(!so_cmp(input, cases.sw[i].s)) return cases.sw[i].e;
    }
    return -1;
}

int so_switch_i(So input, So_Switches cases) {
    for(size_t i = 0; i < cases.len; ++i) {
        if(!so_cmp_i(input, cases.sw[i].s)) return cases.sw[i].e;
    }
    return -1;
}

