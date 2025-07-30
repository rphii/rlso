#include "../src/so.h"
#include "../src/so-cmp.h"
#include "../src/so-file.h"
#include "../src/so-path.h"

int main(int argc, char **argv) {
    So so = {0};
    So out = {0};
    for(int i = 1; i < argc; ++i) {
        So filename = so_l(argv[i]);
        So basename = so_get_basename(filename);
        so_extend(&basename, so(".txt"));
        So clean;
        printf("%u/%u read %.*s\n", i, argc-1, SO_F(filename));
        so_clear(&so);
        int err = 0;
        if(so_file_read(filename, &so)) { err = -1; ERR_PRINTF("  failed reading '%.*s'", SO_F(so_l(argv[i]))); }
        if(so_file_read(filename, &clean)) { err = -1; ERR_PRINTF("  failed reading '%.*s'", SO_F(so_l(argv[i]))); }
        if(so_cmp(so, clean)) { err = -1; ERR_PRINTF("files differ"); }
        else printf("  ::equal -> %.*s\n", SO_F(basename));
        if(err) continue;
        //so_file_write(basename, clean);
        so_fmt(&out, "[%.*s]\n", SO_F(filename));
        so_extend(&out, so);
        so_free(&clean);
        so_free(&basename);
    }
    if(so_file_write(so("out.txt"), out)) THROW_PRINT("failed writing file\n");
    so_free(&so);
    so_free(&out);
}

