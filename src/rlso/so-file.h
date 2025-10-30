#ifndef SO_FILE_H

#include <rlc.h>

typedef struct So So;
typedef int (*So_File_Exec_Callback)(So file, void *user);

#define SO_FILE_PATH_MAX    4096

typedef enum {
    SO_FILE_ERR_OK,
    SO_FILE_ERR_DIR,
    SO_FILE_ERR_OPEN,
    SO_FILE_ERR_BYTES,
    SO_FILE_ERR_INVALID,
    SO_FILE_ERR_RECURSIVE,
    SO_FILE_ERR_CANT_OPEN,
    SO_FILE_ERR_TYPE_CHECK,
} So_File_Err;

typedef enum {
    SO_FILE_TYPE_NONE,
    SO_FILE_TYPE_FILE,
    SO_FILE_TYPE_DIR,
    SO_FILE_TYPE_ERROR,
} So_File_Type_List;

ErrDecl so_file_get_size(So filename, size_t *size);
ErrDecl so_file_get_size_fp(FILE *file, size_t *size);

So_File_Type_List so_file_get_type(So filename);

ErrDecl so_file_read_fp_ext(FILE *file, So *content, size_t n, size_t size, size_t *at);

FILE *so_file_fp(So filename, char *mode);
#define ERR_so_file_read_fp(...) "failed reading file"
ErrDecl so_file_read_fp(FILE *file, So *content);
#define ERR_so_file_read(...) "failed reading file"
ErrDecl so_file_read(So filename, So *content);
#define ERR_so_file_write_fp(...) "failed writing file"
ErrDecl so_file_write_fp(FILE *file, So content);
#define ERR_so_file_write(...) "failed writing file"
ErrDecl so_file_write(So filename, So content);
#define ERR_so_file_exec(...) "failed executing"
ErrDecl so_file_exec(So file_or_dir, bool hidden, bool recursive, So_File_Exec_Callback cb_file, So_File_Exec_Callback cb_dir, void *user);

#define SO_FILE_H
#endif

