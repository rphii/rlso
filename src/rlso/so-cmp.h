#ifndef SO_CMP_H

#include "so-cmp-attr.h"

typedef struct So So;
typedef struct So_Ref So_Ref;
typedef int (*So_Cmp_Func)(So, So);
typedef int (*So_Cmp_Func_p)(So *, So *);

int so_cmp(So a, So b);
int so_cmp_s(So a, So b);
int so_cmp_c(So a, So b);
int so_cmp_cs(So a, So b);
int so_cmp_p(So *a, So *b);
int so_cmp_sp(So *a, So *b);
int so_cmp_cp(So *a, So *b);
int so_cmp_csp(So *a, So *b);

int so_cmp0(So a, So b);
int so_cmp0_s(So a, So b);
int so_cmp0_c(So a, So b);
int so_cmp0_cs(So a, So b);
int so_cmp0_p(So *a, So *b);
int so_cmp0_sp(So *a, So *b);
int so_cmp0_cp(So *a, So *b);
int so_cmp0_csp(So *a, So *b);

int so_cmpE(So a, So b);
int so_cmpE_s(So a, So b);
int so_cmpE_c(So a, So b);
int so_cmpE_cs(So a, So b);
int so_cmpE_p(So *a, So *b);
int so_cmpE_sp(So *a, So *b);
int so_cmpE_cp(So *a, So *b);
int so_cmpE_csp(So *a, So *b);

int so_cmpx(So a, So b, So_Cmp_Attr attr);
int so_cmpx_p(So *a, So *b, So_Cmp_Attr attr);
#if 0
int so_cmpX(So a, So b);
int so_cmpX_p(So *a, So *b);
#endif

#define SO_CMP_H
#endif


