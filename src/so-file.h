#ifndef SO_FILE_H

#include <rphii/err.h>

typedef struct So So;

#define SO_FILE_PATH_MAX    4096

typedef enum {
    SO_FILE_ERR_OK,
    SO_FILE_ERR_DIR,
    SO_FILE_ERR_OPEN,
    SO_FILE_ERR_BYTES,
} So_File_Err;

ErrDecl so_file_read(So filename, So *content);
ErrDecl so_file_write(So filename, So *content);

#define SO_FILE_H
#endif

