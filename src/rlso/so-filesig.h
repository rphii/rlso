#ifndef SO_FILESIG_H

#include "so-core.h"
#include <rlc/err.h>
#include <stddef.h>

typedef enum So_Filesig_List {
    SO_FILESIG_NONE,
    /* keep signatures below */
    SO_FILESIG_SCRIPT,  // starts with #!
    SO_FILESIG_GIF,     // Graphics Interchange Format
    SO_FILESIG_TIFF,    // Tagged Image File Format
    SO_FILESIG_BIGTIFF, // BigTIFF
    SO_FILESIG_OPENEXR, // OpenEXR image
    SO_FILESIG_BPG,     // Better Portable Graphics
    SO_FILESIG_JPEG,    // JPEG (image format)
    SO_FILESIG_JPEG2K,  // JPEG2K (image format)
    SO_FILESIG_QOI,     // Quite OK Image Format
    SO_FILESIG_ZIPLIKE, // zip file formats (zip, aar, apk, docx, epub, ipa, jar, kmz, maff, msix, odp, ods, odt, pk3, pk4, pptx, usdz, vsdx, xlsx, xpi, whl)
    SO_FILESIG_RAR,     // Roshal ARchive
    SO_FILESIG_ELF,     // Executable and Linkable Format
    SO_FILESIG_PNG,     // Portable Graphics Format
    SO_FILESIG_HEIC,    // High Efficiency Image Container
    SO_FILESIG_PDF,     // Portable Document Format
    SO_FILESIG_OGG,     // OGG (open source media container format)
    SO_FILESIG_WAV,     // Waveform Audio File Format
    SO_FILESIG_AVI,     // Audio Video Interleave video format
    SO_FILESIG_MP3,     // MP3 (audio file)
    SO_FILESIG_LZH,     // Lempel Ziv Huffman archive file
    SO_FILESIG_BMP,     // Bitmap
    SO_FILESIG_FLAC,    // Free Lossless Audio Codec
    SO_FILESIG_XAR,     // eXtensible ARchive format
    SO_FILESIG_TAR,     // tar archive
    SO_FILESIG_TOX,     // Open source portable voxel file
    SO_FILESIG_7Z,      // 7-Zip file format
    SO_FILESIG_GZ,      // GZIP compressed file
    SO_FILESIG_XZ,      // XZ compression utility (using lzma2 compression)
    SO_FILESIG_LZ4,     // LZ4 Frame Format (lz4 itself does not offer magic bytes)
    SO_FILESIG_FLIF,    // Free Lossless Image Format
    SO_FILESIG_MKV,     // Matroska Media Container (including webm)
    SO_FILESIG_MPEG4,   // MPEG-4 video file
    SO_FILESIG_ZLIB,    // zlib archive
    SO_FILESIG_LZFSE,   // Lempel Ziv style data compression algorithm using Finite State Entroby coding OSS by Apple
    SO_FILESIG_QCOW,    // qcow file format (disk image)
    /* keep signatures above */
    SO_FILESIG__COUNT,
} So_Filesig_List;

ErrDecl so_filesig_fp(FILE *file, So extension, bool *uncertain, So_Filesig_List *sig);
ErrDecl so_filesig(So path, bool *uncertain, So_Filesig_List *sig);
void so_filesig_fmt(So *out, So_Filesig_List sig);

#define SO_FILESIG_H
#endif // SO_FILESIG_H


