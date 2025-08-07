#include "so-core.h"
#include "so-file.h"
#include "so-as.h"

#include <stdint.h>
#include <rl/err.h>
#include <rl/platform-detect.h>
#include <stdlib.h>
#include <errno.h>

FILE *so_file_fp(So filename, char *mode) {
    /* get clean C string */
    char path[SO_FILE_PATH_MAX];
    so_as_cstr(filename, path, SO_FILE_PATH_MAX);
    FILE *file = fopen(path, mode);
    return file;
}

ErrDecl so_file_read_fp(FILE *file, So *content) {
    ASSERT_ARG(file);
    ASSERT_ARG(content);
    int err = 0;
    /* get file length */
    fseek(file, 0, SEEK_END);
    size_t bytes_file = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);
    if(bytes_file == (SIZE_MAX>>1)) ERR(SO_FILE_ERR_INVALID);
    if(SIZE_IS_NEG(bytes_file)) ERR(SO_FILE_ERR_INVALID);
    /* allocate memory */
    so_resize(content, bytes_file);
    /* read file */
    size_t bytes_read = fread(content->str, 1, bytes_file, file);
    if(bytes_file != bytes_read) ERR(SO_FILE_ERR_BYTES);
    //content->ref.str[bytes_read] = 0;
clean:
    /* close file outside */
    return err;
}

ErrDecl so_file_write_fp(FILE *file, So content) {
    ASSERT_ARG(file);
    int err = 0;
    /* write file */
#if SO_File_CHECK_BYTES_WRITTEN
    size_t bytes_written = 
#endif
        fwrite(content.str, 1, content.len, file);
#if SO_File_CHECK_BYTES_WRITTEN
    if(bytes_written != ref.len) ERR(SO_FILE_ERR_BYTES);
clean:
#endif
    /* close file outside */
    return err;
}


ErrDecl so_file_read(So filename, So *content) {
    ASSERT_ARG(content);
    int err = 0;
    FILE *file = 0;
    /* open the file */
    errno = 0;
    if(filename.len && (
                filename.str[filename.len - 1] == PLATFORM_CH_SUBDIR ||
                filename.str[filename.len - 1] == '/')) {
        ERR(SO_FILE_ERR_DIR);
    }
    /* open and read */
    file = so_file_fp(filename, "r");
    if(!file || errno) ERR(SO_FILE_ERR_OPEN);
    err = so_file_read_fp(file, content);
clean:
    /* close file */
    if(file) fclose(file);
    return err;
}

ErrDecl so_file_write(So filename, So content) {
    int err = 0;
    FILE *file = 0;
    /* open the file */
    errno = 0;
    if(filename.len && (
                filename.str[filename.len - 1] == PLATFORM_CH_SUBDIR ||
                filename.str[filename.len - 1] == '/')) {
        ERR(SO_FILE_ERR_DIR);
    }
    /* open and read */
    file = so_file_fp(filename, "w");
    if(!file || errno) ERR(SO_FILE_ERR_OPEN);
    err = so_file_write_fp(file, content);
clean:
    /* close file */
    if(file) fclose(file);
    return err;
}


