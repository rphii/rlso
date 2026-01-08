#include "so-switch.h"
#include "so-cmp.h"

int _so_switch(So input, So_Switch *cases, size_t len) {
    for(size_t i = 0; i < len; ++i) {
        if(!so_cmp(input, cases[i].s)) return cases[i].e;
    }
    return -1;
}

int _so_switch_i(So input, So_Switch *cases, size_t len) {
    for(size_t i = 0; i < len; ++i) {
        if(!so_cmp_i(input, cases[i].s)) return cases[i].e;
    }
    return -1;
}

