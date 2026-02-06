#include "../src/rlso.h"
#include <unistd.h>
#include <linux/limits.h>


int main(void) {

    char ccwd[SO_FILE_PATH_MAX] = {0};
    getcwd(ccwd, SO_FILE_PATH_MAX);

    So cwd = so_l(ccwd);
    so_path_get_realpath(&cwd, cwd);

    So nodir = so_get_dir(cwd);
    So check = SO;
    so_path_join(&check, cwd, so(".."));

    so_path_get_realpath(&check, check);
    int result = so_cmp(check, nodir);

    so_free(&cwd);
    so_free(&check);

    return result;
}

