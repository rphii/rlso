#ifndef SO_FILE_H

#include <rl/err.h>

typedef struct So So;

#define SO_FILE_PATH_MAX    4096

typedef enum {
    SO_FILE_ERR_OK,
    SO_FILE_ERR_DIR,
    SO_FILE_ERR_OPEN,
    SO_FILE_ERR_BYTES,
    SO_FILE_ERR_INVALID,
} So_File_Err;

FILE *so_file_fp(So filename, char *mode);
ErrDecl so_file_read_fp(FILE *file, So *content);
ErrDecl so_file_read(So filename, So *content);
ErrDecl so_file_write_fp(FILE *file, So content);
ErrDecl so_file_write(So filename, So content);

#define SO_FILE_H
#endif

