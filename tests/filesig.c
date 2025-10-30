#include "../src/rlso.h"

void test(So path) {
    FILE *fp = so_file_fp(path, "r");
    if(!fp) {
        //printf("invalid: %.*s\n", SO_F(path));
        return;
    }
    So_Filesig_List fs;
    bool uncertain;
    so_filesig_fp(fp, so_get_ext(path), &uncertain, &fs);
    fclose(fp);
    So tmp = SO;
    So out = SO;
    so_filesig_fmt(&tmp, fs);
    so_fmt(&out, "%10.*s -- %u -- %.*s", SO_F(tmp), uncertain, SO_F(path));
    so_println(out);
    so_free(&tmp);
    so_free(&out);
}

int main(int argc, char **argv) {

    So in = SO;
    while(true) {
        so_input(&in);
        if(!so_len(in) && getchar() == EOF) break;
        test(in);
        so_clear(&in);
    }

    so_free(&in);
#if 0
    for(size_t i = 1; i < argc; ++i) {
        test(so_l(argv[i]));
    }
#endif

    return 0;
}

