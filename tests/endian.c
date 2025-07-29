#include "test.h"

int main(void) {
    So so = { .stack.len = SO_STACK_HEAP_BIT };
    EXPECT(so.ref.len, SO_HEAP_BIT);
    return 0;
}

