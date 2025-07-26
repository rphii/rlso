#include "test.h"
int main(void) {
    EXPECT(so_len(so("a")), 1);
    return 0;
}

