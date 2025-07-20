#ifndef VSO_H

#include "so.h"
typedef So *Vso;

void vso_push(Vso *v, So so);
So vso_pop(Vso *v);
void vso_free(Vso *v);

#define VSO_H
#endif

