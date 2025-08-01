#include "test.h"

int main(int argc, char **argv) {
    So dir = so("abcdefghi"), base = so("jklmnopqr"), ext = so(".stuvwxyz"), noext = SO, nodir = SO;
    so_path_join(&dir, so("xxx"), dir);
    so_path_join(&noext, dir, base);
    So full = so_clone(noext);
    so_extend(&full, ext);
    printf("v full\n  ");
    so_println(full);
    so_extend(&nodir, base);
    so_extend(&nodir, ext);
    So so;
    printf("v basename\n");
    so = so_get_basename(full);
    EXPECT_CMP(so, base);
    printf("v dir\n");
    so = so_get_dir(full);
    EXPECT_CMP(so, dir);
    printf("v ext\n");
    so = so_get_ext(full);
    EXPECT_CMP(so, ext);
    printf("v nodir\n");
    so = so_get_nodir(full);
    EXPECT_CMP(so, nodir);
    printf("v noext\n");
    so = so_get_noext(full);
    EXPECT_CMP(so, noext);
    so_free(&nodir);
    so_free(&noext);
    so_free(&full);
    so_free(&dir);
    return 0;
}


