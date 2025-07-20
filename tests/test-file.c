#include "../src/so.h"
#include "../src/so-file.h"

int main(int argc, char **argv) {
    So so = {0};
    So out = {0};
    for(int i = 1; i < argc; ++i) {
        so_clear(&so);
        so_file_read(so_l(argv[i]), &so);
        so_extend(&out, so);
        printf("%.*s\n", SO_F(so));
    }
    so_file_write(so("out.txt"), out);
    so_free(&so);
}

