#ifndef SO_PRINT

typedef struct So So;

#include <stdio.h>

void so_print(So so);
void so_println(So so);
void so_printdbg(So so);

void so_fprint(FILE *fp, So so);
void so_fprintln(FILE *fp, So so);
void so_fprintdbg(FILE *fp, So so);

#define SO_PRINT
#endif

