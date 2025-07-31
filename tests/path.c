#include "test.h"

int main(int argc, char **argv) {
    So nodir = SO;
    so_path_join(&nodir, so("a"), so("b"));
    So full = so_clone(nodir);
    so_extend(&full, so(".c"));
    So so;
    so = so_get_basename(full);
    EXPECT_CMP(so, so("b"));
    so = so_get_dir(full);
    EXPECT_CMP(so, so("a"));
    so = so_get_ext(full);
    EXPECT_CMP(so, so(".c"));
    so = so_get_nodir(full);
    EXPECT_CMP(so, so("b.c"));
    so = so_get_noext(full);
    EXPECT_CMP(so, nodir);
    so_free(&nodir);
    so_free(&full);
    return 0;
}

