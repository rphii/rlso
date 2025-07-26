#include "../src/so.h"
#include "../src/so-file.h"

int main(int argc, char **argv) {
    So so = {0};
    So out = {0};
    for(int i = 1; i < argc; ++i) {
        printf("%u/%u read %.*s\n", i, argc-1, SO_F(so_l(argv[i])));
        so_clear(&so);
        if(so_file_read(so_l(argv[i]), &so)) ERR_PRINTF("  failed reading '%.*s'", SO_F(so_l(argv[i])));
        so_extend(&out, so);
    }
    if(so_file_write(so("out.txt"), out)) THROW_PRINT("failed writing file\n");
    so_free(&so);
}

