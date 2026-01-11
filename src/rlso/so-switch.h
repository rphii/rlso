#ifndef RLSO_SWITCH_H

#include <rlc/err.h>
#include "so-core.h"

typedef struct So_Switch {
    int e; /* enum */
    So s; /* string */
} So_Switch;

typedef struct So_Switches {
    So_Switch *sw; /* cases */
    size_t len; /* number of cases */
} So_Switches;

int so_switch(So input, int default_case, So_Switches cases);
int so_switch_i(So input, int default_case, So_Switches cases);

#define So_Switch_Pair(E, S) \
    (So_Switch){ \
        .e = (E), \
        .s = (S) \
    }

#define So_Switches(...) \
    (So_Switches){ \
        .sw = SO_SWITCH_FACTORY(__VA_ARGS__), \
        .len = sizeof(SO_SWITCH_FACTORY(__VA_ARGS__))/sizeof(So_Switch) \
    }

/* helper macros {{{ */

#define SO_SWITCH_FACTORY(...) \
    (So_Switch []){ \
        __VA_OPT__(SO_SWITCH_EXPAND(SO_SWITCH_HELPER(__VA_ARGS__))) \
    } 

#define SO_SWITCH_HELPER(E, S, ...) \
    So_Switch_Pair(E, S), \
    __VA_OPT__(SO_SWITCH_AGAIN SO_SWITCH_PARENS (__VA_ARGS__))
#define SO_SWITCH_AGAIN() SO_SWITCH_HELPER

#define SO_SWITCH_PARENS ()

#define SO_SWITCH_EXPAND(...)  SO_SWITCH_EXPAND4(SO_SWITCH_EXPAND4(SO_SWITCH_EXPAND4(SO_SWITCH_EXPAND4(__VA_ARGS__))))
#define SO_SWITCH_EXPAND4(...) SO_SWITCH_EXPAND3(SO_SWITCH_EXPAND3(SO_SWITCH_EXPAND3(SO_SWITCH_EXPAND3(__VA_ARGS__))))
#define SO_SWITCH_EXPAND3(...) SO_SWITCH_EXPAND2(SO_SWITCH_EXPAND2(SO_SWITCH_EXPAND2(SO_SWITCH_EXPAND2(__VA_ARGS__))))
#define SO_SWITCH_EXPAND2(...) SO_SWITCH_EXPAND1(SO_SWITCH_EXPAND1(SO_SWITCH_EXPAND1(SO_SWITCH_EXPAND1(__VA_ARGS__))))
#define SO_SWITCH_EXPAND1(...) __VA_ARGS__

/* helper macros }}} */

#define RLSO_SWITCH_H
#endif /* RLSO_SWITCH_H */

