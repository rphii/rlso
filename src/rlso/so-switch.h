#ifndef RLSO_SWITCH_H

#include <rlc/err.h>
#include "so-core.h"

typedef struct So_Switch {
    int e; /* enum */
    So s; /* string */
} So_Switch;

//#define So_Switches(...)  (So_Switch[]){ __VA_ARGS__ }

#define So_Switch_End           0
#define So_Switch_Pair(E, S)    (So_Switch){ .e = (E), .s = (S) }

#define so_switch(input, cases)     _so_switch((input), (cases), sizeof((cases))/sizeof(*(cases)))
#define so_switch_i(input, cases)   _so_switch_i((input), (cases), sizeof((cases))/sizeof(*(cases)))

int _so_switch(So input, So_Switch *cases, size_t len);
int _so_switch_i(So input, So_Switch *cases, size_t len);



#define RLSO_SWITCH_H
#endif /* RLSO_SWITCH_H */

