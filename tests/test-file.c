#include "../src/so.h"
#include "../src/so-file.h"

int main(int argc, char **argv) {
    So so = {0};
    So out = {0};
    for(int i = 1; i < argc; ++i) {
        so_clear(&so);
        if(so_file_read(so_l(argv[i]), &so)) THROW_PRINT("failed reading '%.*s'", SO_F(so_l(argv[i])));
        so_extend(&out, so);
        printf("%.*s\n", SO_F(so));
    }
    if(so_file_write(so("out.txt"), out)) THROW_PRINT("failed writing file\n");
    so_free(&so);
}

