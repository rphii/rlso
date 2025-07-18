#include "so.h"
#include "so-file.h"
#include "so-as.h"

#include <rphii/err.h>
#include <rphii/platform-detect.h>
#include <stdlib.h>
#include <errno.h>

ErrDecl so_file_read_fp(FILE *file, So *content) {
    ASSERT_ARG(file);
    ASSERT_ARG(content);
    int err = 0;
    /* get file length */
    fseek(file, 0, SEEK_END);
    size_t bytes_file = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);
    /* allocate memory */
    so_resize(content, bytes_file);
    /* read file */
    size_t bytes_read = fread(content->ref.str, 1, bytes_file, file);
    if(bytes_file != bytes_read) ERR(SO_FILE_ERR_BYTES);
    content->ref.str[bytes_read] = 0;
clean:
    /* close file outside */
    return err;
}

int so_file_write_fp(FILE *file, So *content) {
    ASSERT_ARG(file);
    ASSERT_ARG(content);
    int err = 0;
    /* write file */
    So_Ref ref = _so_ref(content);
    size_t bytes_written = fwrite(ref.str, 1, ref.len, file);
    if(bytes_written != ref.len) ERR(SO_FILE_ERR_BYTES);
clean:
    /* close file outside */
    return err;
}


ErrDecl so_file_read(So filename, So *content) {
    ASSERT_ARG(content);
    int err = 0;
    FILE *file = 0;
    /* open the file */
    errno = 0;
    So_Ref ref = so_ref(filename);
    if(ref.len && (
                ref.str[ref.len] == PLATFORM_CH_SUBDIR ||
                ref.str[ref.len] == '/')) {
        ERR(SO_FILE_ERR_DIR);
    }
    /* get clean C string */
    char path[SO_FILE_PATH_MAX];
    so_as_cstr(filename, path, SO_FILE_PATH_MAX);
    /* open and read */
    file = fopen(path, "r");
    if(!file || errno) ERR(SO_FILE_ERR_OPEN);
    err = so_file_read_fp(file, content);
clean:
    /* close file */
    if(file) fclose(file);
    return err;
}

ErrDecl so_file_write(So filename, So *content) {
    ASSERT_ARG(content);
    int err = 0;
    FILE *file = 0;
    /* open the file */
    errno = 0;
    So_Ref ref = so_ref(filename);
    if(ref.len && (
                ref.str[ref.len] == PLATFORM_CH_SUBDIR ||
                ref.str[ref.len] == '/')) {
        ERR(SO_FILE_ERR_DIR);
    }
    /* get clean C string */
    char path[SO_FILE_PATH_MAX];
    so_as_cstr(filename, path, SO_FILE_PATH_MAX);
    /* open and write */
    file = fopen(path, "w");
    if(!file || errno) ERR(SO_FILE_ERR_OPEN);
    err = so_file_write_fp(file, content);
clean:
    /* close file */
    if(file) fclose(file);
    return err;
}


