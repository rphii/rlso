#include "so-core.h"
#include "so-file.h"
#include "so-as.h"
#include "so-path.h"
#include "so-cmp.h"

#include <stdint.h>
#include <rlc.h>
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


size_t so_file_get_size(So filename) {/*{{{*/
    char path[SO_FILE_PATH_MAX];
    so_as_cstr(filename, path, SO_FILE_PATH_MAX);
    FILE *fp = fopen(path, "rb");
    size_t result = SIZE_MAX;
    if(fp) {
        if(!fseek(fp, 0L, SEEK_END)) {
            result = ftell(fp);
        }
        fclose(fp);
    }
    return result;
}/*}}}*/

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


#include <sys/stat.h>
#include <dirent.h>

So_File_Type_List so_file_get_type(So filename) {
    struct stat s;
    char path[SO_FILE_PATH_MAX];
    so_as_cstr(filename, path, SO_FILE_PATH_MAX);
    int r = lstat(path, &s);
    if(r) return SO_FILE_TYPE_ERROR;
    if(S_ISREG(s.st_mode)) return SO_FILE_TYPE_FILE;
    if(S_ISDIR(s.st_mode)) return SO_FILE_TYPE_DIR;
    return SO_FILE_TYPE_ERROR;
}

ErrDecl so_file_exec(So file_or_dir, bool hidden, bool recursive, So_File_Exec_Callback cb_file, So_File_Exec_Callback cb_dir, void *user) {
    int err = 0;
    DIR *dir = 0;
    int fails = 0;
    So dot = so(".");
    So dotdot = so("..");
    if(!so_len(file_or_dir)) return 0;
    So_File_Type_List type = so_file_get_type(file_or_dir);
    So filename = {0};
    if(type == SO_FILE_TYPE_DIR) {
        if(!recursive) {
            ERR(SO_FILE_ERR_RECURSIVE);
        }
        struct dirent *dp = 0;
        So direns = so_ensure_dir(file_or_dir);
        char cdir[SO_FILE_PATH_MAX];
        so_as_cstr(direns, cdir, SO_FILE_PATH_MAX);
        if((dir = opendir(cdir)) == NULL) {
            ERR(SO_FILE_ERR_CANT_OPEN);
        }
        while((dp = readdir(dir)) != NULL) {
            So dname = so_l(dp->d_name);
            if(!so_cmp(dname, dot)) continue;
            if(!so_cmp(dname, dotdot)) continue;
            if(!hidden && !so_cmp0(dname, dot)) continue;
            so_extend(&filename, direns);
            if(so_len(direns) > 1) so_push(&filename, PLATFORM_CH_SUBDIR);
            so_extend(&filename, dname);
            if(!so_len(filename)) {
                so_clear(&filename);
                continue;
            }
            So_File_Type_List type2 = so_file_get_type(filename);
            if(cb_dir && type2 == SO_FILE_TYPE_DIR) {
                fails += (bool)cb_dir(filename, user);
            } else if(cb_file && type2 == SO_FILE_TYPE_FILE) {
                fails += (bool)cb_file(filename, user);
            }
            so_clear(&filename);
        }
        if(dir) {
            closedir(dir);
            dir = 0;
        }
    } else if(cb_file && type == SO_FILE_TYPE_FILE) {
        fails += (bool)cb_file(file_or_dir, user);
    } else if(type == SO_FILE_TYPE_ERROR) {
        fails += (bool)SO_FILE_ERR_TYPE_CHECK;
    } else {
        //info(INFO_skipping_nofile_nodir, "skipping '%.*s' since no regular file nor directory", SO_F(*file_or_dir));
    }
clean:
    so_free(&filename);
    if(dir) closedir(dir);
    return fails + err;
}

