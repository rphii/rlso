#include "test.h"

int main(int argc, char **argv) {
    So s = so("somepath.txt");
    EXPECT_CMP(so_get_noext(s), so("somepath"));
    return 0;
}

