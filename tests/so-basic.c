#include <rlc/err.h>
#include "test.h"

#define EXPECT(expr, val)   \
    ASSERT(expr == val, "expected true")

int main(void) {
    EXPECT(so_is_empty(so(0)), true);
    EXPECT(so_is_empty(so("")), true);
    EXPECT(so_is_empty(so("a")), false);
    EXPECT(so_len(so(0)), 0);
    EXPECT(so_len(so("a")), 1);
    EXPECT(so_len(so("abc")), 3);
    return 0;
}

