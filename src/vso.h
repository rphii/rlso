#ifndef VSO_H

#include "so.h"
typedef So *VSo;

void vso_push(VSo *v, So so);
So vso_pop(VSo *v);
void vso_free(VSo *v);

#define VSO_H
#endif

