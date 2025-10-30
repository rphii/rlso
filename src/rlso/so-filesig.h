#ifndef SO_FILESIG_H

#include "so-core.h"
#include <rlc/err.h>
#include <stddef.h>

typedef enum So_Filesig_List {
    SO_FILESIG_NONE,
    /* keep signatures below */
    SO_FILESIG_SCRIPT,
    SO_FILESIG_GIF,
    SO_FILESIG_TIFF,
    SO_FILESIG_BIGTIFF,
    SO_FILESIG_OPENEXR,
    SO_FILESIG_BPG,
    SO_FILESIG_JPEG,
    SO_FILESIG_JPEG2K,
    SO_FILESIG_QOI,
    SO_FILESIG_ZIPLIKE,
    SO_FILESIG_RAR,
    SO_FILESIG_ELF,
    SO_FILESIG_PNG,
    SO_FILESIG_HEIC,
    SO_FILESIG_PDF,
    SO_FILESIG_OGG,
    SO_FILESIG_WAV,
    SO_FILESIG_AVI,
    SO_FILESIG_MP3,
    SO_FILESIG_LZH,
    SO_FILESIG_BMP,
    SO_FILESIG_FLAC,
    SO_FILESIG_XAR,
    SO_FILESIG_TAR,
    SO_FILESIG_TOX,
    SO_FILESIG_7Z,
    SO_FILESIG_GZ,
    SO_FILESIG_XZ,
    SO_FILESIG_LZ4,
    SO_FILESIG_FLIF,
    SO_FILESIG_MKV,
    SO_FILESIG_MPEG4,
    SO_FILESIG_ZLIB,
    SO_FILESIG_LZFSE,
    SO_FILESIG_QCOW,
    /* keep signatures above */
    SO_FILESIG__COUNT,
} So_Filesig_List;

ErrDecl so_filesig_fp(FILE *file, So extension, bool *uncertain, So_Filesig_List *sig);
void so_filesig_fmt(So *out, So_Filesig_List sig);

#define SO_FILESIG_H
#endif // SO_FILESIG_H


