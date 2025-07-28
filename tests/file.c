#include "test.h"

int main(int argc, char **argv) {
    So content = SO;
    So filename = so_l(argv[0]);
    NEXPECT(so_file_read(so("asdflkjh"), &content), 0);
    EXPECT(so_is_zero(content), true);
    EXPECT(so_file_read(filename, &content), 0);
    printf("len %zu bytes\n", so_len(content));
    so_extend(&filename, so(".tmp"));
    so_print(so("outname: "));
    so_println(filename);
    EXPECT(so_file_write(filename, content), 0);
    so_free(&content);
    so_free(&filename);
    return 0;
}

