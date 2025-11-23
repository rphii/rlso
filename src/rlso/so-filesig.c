#include "../rlso.h"
#include "so-filesig.h"

typedef bool (*So_Filesig_Callback)(So extension, So content, bool *uncertain);

/* prototypes {{{ */

bool so_filesig_cb_script(So extension, So content, bool *uncertain);
bool so_filesig_cb_gif(So extension, So content, bool *uncertain);
bool so_filesig_cb_tiff(So extension, So content, bool *uncertain);
bool so_filesig_cb_bigtiff(So extension, So content, bool *uncertain);
bool so_filesig_cb_openexr(So extension, So content, bool *uncertain);
bool so_filesig_cb_bpg(So extension, So content, bool *uncertain);
bool so_filesig_cb_jpeg(So extension, So content, bool *uncertain);
bool so_filesig_cb_jpeg2k(So extension, So content, bool *uncertain);
bool so_filesig_cb_qoi(So extension, So content, bool *uncertain);
bool so_filesig_ziplike(So extension, So content, bool *uncertain);
bool so_filesig_cb_rar(So extension, So content, bool *uncertain);
bool so_filesig_cb_elf(So extension, So content, bool *uncertain);
bool so_filesig_cb_png(So extension, So content, bool *uncertain);
bool so_filesig_cb_heic(So extension, So content, bool *uncertain);
bool so_filesig_cb_pdf(So extension, So content, bool *uncertain);
bool so_filesig_cb_ogg(So extension, So content, bool *uncertain);
bool so_filesig_cb_wav(So extension, So content, bool *uncertain);
bool so_filesig_cb_avi(So extension, So content, bool *uncertain);
bool so_filesig_cb_mp3(So extension, So content, bool *uncertain);
bool so_filesig_cb_lzh(So extension, So content, bool *uncertain);
bool so_filesig_cb_bmp(So extension, So content, bool *uncertain);
bool so_filesig_cb_flac(So extension, So content, bool *uncertain);
bool so_filesig_cb_xar(So extension, So content, bool *uncertain);
bool so_filesig_cb_tar(So extension, So content, bool *uncertain);
bool so_filesig_cb_tox(So extension, So content, bool *uncertain);
bool so_filesig_cb_7z(So extension, So content, bool *uncertain);
bool so_filesig_cb_gz(So extension, So content, bool *uncertain);
bool so_filesig_cb_xz(So extension, So content, bool *uncertain);
bool so_filesig_cb_lz4(So extension, So content, bool *uncertain);
bool so_filesig_cb_flif(So extension, So content, bool *uncertain);
bool so_filesig_cb_mkv(So extension, So content, bool *uncertain);
bool so_filesig_cb_mpeg4(So extension, So content, bool *uncertain);
bool so_filesig_cb_zlib(So extension, So content, bool *uncertain);
bool so_filesig_cb_lzfse(So extension, So content, bool *uncertain);
bool so_filesig_cb_qcow(So extension, So content, bool *uncertain);

/* prototypes }}} */

/* implementations */

inline bool so_filesig_cb_script(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("#!"))) {
        *uncertain = false;
        return true;
    }
    return false;
}

inline bool so_filesig_cb_gif(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("GIF87")) || !so_cmp0(content, so("GIF89a"))) {
        *uncertain = true;
        return true;
    }
    return false;
}

inline bool so_filesig_cb_tiff(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("II*\x00")) || !so_cmp0(content, so("II\x00*"))) {
        *uncertain = !(!so_cmp(extension, so(".tif")) || !so_cmp(extension, so(".tiff")));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_bigtiff(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("II+\x00")) || !so_cmp0(content, so("II\x00+"))) {
        *uncertain = !(!so_cmp(extension, so(".tif")) || !so_cmp(extension, so(".tiff")));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_openexr(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("v/1\x01"))) {
        *uncertain = so_cmp(extension, so(".exr"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_bpg(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("BPG\xFB"))) {
        *uncertain = true;
        return true;
    }
    return false;
}

inline bool so_filesig_cb_jpeg(So extension, So content, bool *uncertain) {
    bool result = false;
    //if (!so_cmp0(content, so("\xFF\xD8\xFF\xDB")) || !so_cmp0(content, so("\xFF\xD8\xFF\xE0\x00\x10JFIF\x00\x01")) ||
    //    !so_cmp0(content, so("\xFF\xD8\xFF\xEE")) || !so_cmp0(content, so("\xFF\xD8\xFF\xE0"))) {
    if (!so_cmp0(content, so("\xFF\xD8\xFF"))) {
        result = true;
    }
    if (!so_cmp0(content, so("\xFF\xD8\xFF\xE1"))) {
        if (so_len(content) > 6 && !so_cmp0(so_i0(content, 6), so("\xFF\xD8\xFF\xE1"))) {
            result = true;
        }
    }
    if(result) {
        *uncertain = !(!so_cmp(extension, so(".jpg")) || !so_cmp(extension, so(".jpeg")));
    }
    return result;
}

inline bool so_filesig_cb_jpeg2k(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("\x00\x00\x00\x0CjP\x20\x20\x0D\x0A\x87\x0A")) ||
        !so_cmp0(content, so("\xFF\x4F\xFF\x51"))) {
        *uncertain = !(
                !so_cmp(extension, so(".jp2")) ||
                !so_cmp(extension, so(".j2k")) ||
                !so_cmp(extension, so(".jpf")) ||
                !so_cmp(extension, so(".jpm")) ||
                !so_cmp(extension, so(".jpg2")) ||
                !so_cmp(extension, so(".j2c")) ||
                !so_cmp(extension, so(".jpc")) ||
                !so_cmp(extension, so(".jpx")) ||
                !so_cmp(extension, so(".mj2")));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_qoi(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("qoif"))) {
        *uncertain = true;
        return true;
    }
    return false;
}

inline bool so_filesig_ziplike(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("PK\x03\x04")) || 
        !so_cmp0(content, so("PK\x05\x06")) ||
        !so_cmp0(content, so("PK\x07\x08"))) {
        *uncertain = !(
                !so_cmp(extension, so(".zip")) ||
                !so_cmp(extension, so(".aar")) ||
                !so_cmp(extension, so(".apk")) ||
                !so_cmp(extension, so(".docx")) ||
                !so_cmp(extension, so(".epub")) ||
                !so_cmp(extension, so(".ipa")) ||
                !so_cmp(extension, so(".jar")) ||
                !so_cmp(extension, so(".kmz")) ||
                !so_cmp(extension, so(".maff")) ||
                !so_cmp(extension, so(".msix")) ||
                !so_cmp(extension, so(".odp")) ||
                !so_cmp(extension, so(".ods")) ||
                !so_cmp(extension, so(".odt")) ||
                !so_cmp(extension, so(".pk3")) ||
                !so_cmp(extension, so(".pk4")) ||
                !so_cmp(extension, so(".pptx")) ||
                !so_cmp(extension, so(".usdz")) ||
                !so_cmp(extension, so(".vsdx")) ||
                !so_cmp(extension, so(".xlsx")) ||
                !so_cmp(extension, so(".xpl")) ||
                !so_cmp(extension, so(".whl")));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_rar(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("Rar!\x1A\x07\x00")) ||
        !so_cmp0(content, so("Rar!\x1A\x07\x01\x00"))) {
        *uncertain = so_cmp(extension, so(".rar"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_elf(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("\x7F\x45\x4C\x46"))) {
        *uncertain = so_cmp(extension, so(".elf"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_png(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("\x89PNG\x0D\x0A\x1A\x0A"))) {
        *uncertain = so_cmp(extension, so(".png"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_heic(So extension, So content, bool *uncertain) {
    if (so_len(content) > 4 && !so_cmp0(so_i0(content, 4), so("ftypheic"))) {
        *uncertain = true;
        return true;
    }
    return false;
}

inline bool so_filesig_cb_pdf(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("%PDF-"))) {
        *uncertain = true;
        return true;
    }
    return false;
}

inline bool so_filesig_cb_ogg(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("OggS"))) {
        *uncertain = true;
        return true;
    }
    return false;
}

inline bool so_filesig_cb_wav(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("RIFF"))) {
        if (so_len(content) > 8 && !so_cmp0(so_i0(content, 8), so("WAVE"))) {
            *uncertain = true;
            return true;
        }
    }
    return false;
}

inline bool so_filesig_cb_avi(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("RIFF"))) {
        if (so_len(content) > 8 && !so_cmp0(so_i0(content, 8), so("AVI\x20"))) {
            *uncertain = true;
            return true;
        }
    }
    return false;
}

inline bool so_filesig_cb_mp3(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("\xFF\xFB")) ||
        !so_cmp0(content, so("\xFF\xF3")) ||
        !so_cmp0(content, so("\xFF\xF2"))) {
        *uncertain = so_cmp(extension, so(".mp3"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_lzh(So extension, So content, bool *uncertain) {
    if (so_len(content) > 2) {
        if (!so_cmp0(content, so("-lh0-")) ||
            !so_cmp0(content, so("-lh5-"))) {
            *uncertain = true;
            return true;
        }
    }
    return false;
}

inline bool so_filesig_cb_bmp(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("BM"))) {
        *uncertain = !(
                !so_cmp(extension, so(".bmp")) ||
                !so_cmp(extension, so(".dib")));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_flac(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("fLaC"))) {
        *uncertain = true;
        return true;
    }
    return false;
}

inline bool so_filesig_cb_xar(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("xar!"))) {
        *uncertain = true;
        return true;
    }
    return false;
}

inline bool so_filesig_cb_tar(So extension, So content, bool *uncertain) {
    if(so_len(content) > 257) {
        if (!so_cmp0(so_i0(content, 257), so("ustar\x00\x30\x30")) ||
            !so_cmp0(so_i0(content, 257), so("ustar\x20\x20\x00"))) {
            *uncertain = so_cmp(extension, so(".tar"));
            return true;
        }
    }
    return false;
}

inline bool so_filesig_cb_tox(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("tox3"))) {
        *uncertain = true;
        return true;
    }
    return false;
}

inline bool so_filesig_cb_7z(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("7z\xBC\xAF\x27\x1C"))) {
        *uncertain = so_cmp(extension, so(".7z"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_gz(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("7z\xBC\xAF\x27\x1C"))) {
        *uncertain = so_cmp(extension, so(".7z"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_xz(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("\xFD" "7zXZ\x00"))) {
        *uncertain = !(
                !so_cmp(extension, so(".xz")) ||
                !so_cmp(extension, so(".tar.xz")));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_lz4(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("\x04\x22\x4D\x18"))) {
        *uncertain = so_cmp(extension, so(".lz4"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_flif(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("FLIF"))) {
        *uncertain = so_cmp(extension, so(".flif"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_mkv(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("\x1A\x45\xDF\xA3"))) {
        *uncertain = !(
                !so_cmp(extension, so(".mkv")) ||
                !so_cmp(extension, so(".mka")) ||
                !so_cmp(extension, so(".mks")) ||
                !so_cmp(extension, so(".mk3d")) ||
                !so_cmp(extension, so(".webm")));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_mpeg4(So extension, So content, bool *uncertain) {
    if (so_len(content) > 4) {
        if (!so_cmp0(so_i0(content, 4), so("ftypisom")) ||
            !so_cmp0(so_i0(content, 4), so("ftypMSNV"))) {
            *uncertain = true;
            return true;
        }
    }
    return false;
}

inline bool so_filesig_cb_zlib(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("x\x01")) ||
        !so_cmp0(content, so("x\x5E")) ||
        !so_cmp0(content, so("x\x9C")) ||
        !so_cmp0(content, so("x\xDA")) ||
        !so_cmp0(content, so("x\x20")) ||
        !so_cmp0(content, so("x\x7D")) ||
        !so_cmp0(content, so("x\xBB")) ||
        !so_cmp0(content, so("x\xF9"))) {
        *uncertain = so_cmp(extension, so(".zlib"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_lzfse(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("bfx2"))) {
        *uncertain = so_cmp(extension, so(".lzfse"));
        return true;
    }
    return false;
}

inline bool so_filesig_cb_qcow(So extension, So content, bool *uncertain) {
    if (!so_cmp0(content, so("QFI"))) {
        *uncertain = so_cmp(extension, so(".qcow"));
        return true;
    }
    return false;
}

static So_Filesig_Callback so_filesig_callbacks[SO_FILESIG__COUNT] = {
    [SO_FILESIG_SCRIPT] = so_filesig_cb_script,
    [SO_FILESIG_GIF] = so_filesig_cb_gif,
    [SO_FILESIG_TIFF] = so_filesig_cb_tiff,
    [SO_FILESIG_BIGTIFF] = so_filesig_cb_bigtiff,
    [SO_FILESIG_OPENEXR] = so_filesig_cb_openexr,
    [SO_FILESIG_BPG] = so_filesig_cb_bpg,
    [SO_FILESIG_JPEG] = so_filesig_cb_jpeg,
    [SO_FILESIG_JPEG2K] = so_filesig_cb_jpeg2k,
    [SO_FILESIG_QOI] = so_filesig_cb_qoi,
    [SO_FILESIG_ZIPLIKE] = so_filesig_ziplike,
    [SO_FILESIG_RAR] = so_filesig_cb_rar,
    [SO_FILESIG_ELF] = so_filesig_cb_elf,
    [SO_FILESIG_PNG] = so_filesig_cb_png,
    [SO_FILESIG_HEIC] = so_filesig_cb_heic,
    [SO_FILESIG_PDF] = so_filesig_cb_pdf,
    [SO_FILESIG_OGG] = so_filesig_cb_ogg,
    [SO_FILESIG_WAV] = so_filesig_cb_wav,
    [SO_FILESIG_AVI] = so_filesig_cb_avi,
    [SO_FILESIG_MP3] = so_filesig_cb_mp3,
    [SO_FILESIG_LZH] = so_filesig_cb_lzh,
    [SO_FILESIG_BMP] = so_filesig_cb_bmp,
    [SO_FILESIG_FLAC] = so_filesig_cb_flac,
    [SO_FILESIG_XAR] = so_filesig_cb_xar,
    [SO_FILESIG_TAR] = so_filesig_cb_tar,
    [SO_FILESIG_TOX] = so_filesig_cb_tox,
    [SO_FILESIG_7Z] = so_filesig_cb_7z,
    [SO_FILESIG_GZ] = so_filesig_cb_gz,
    [SO_FILESIG_XZ] = so_filesig_cb_xz,
    [SO_FILESIG_LZ4] = so_filesig_cb_lz4,
    [SO_FILESIG_FLIF] = so_filesig_cb_flif,
    [SO_FILESIG_MKV] = so_filesig_cb_mkv,
    [SO_FILESIG_MPEG4] = so_filesig_cb_mpeg4,
    [SO_FILESIG_ZLIB] = so_filesig_cb_zlib,
    [SO_FILESIG_LZFSE] = so_filesig_cb_lzfse,
    [SO_FILESIG_QCOW] = so_filesig_cb_qcow,
};

ErrImpl so_filesig_fp(FILE *file, So extension, bool *uncertain, So_Filesig_List *sig) {
    ASSERT_ARG(file);
    ASSERT_ARG(uncertain);
    ASSERT_ARG(sig);
    int err = 0;
    size_t file_len = 0;
    So content = SO;
    err = so_file_get_size_fp(file, &file_len);
    if(err) ERR(err);
    so_file_read_fp_ext(file, &content, 276, file_len, 0);

    for(size_t i = SO_FILESIG_NONE + 1; i < SO_FILESIG__COUNT; ++i) {
        So_Filesig_Callback cb = so_filesig_callbacks[i];
        if(!cb) continue;
        if(cb(extension, content, uncertain)) {
            *sig = i;
            break;
        }
        if(i + 1 >= SO_FILESIG__COUNT) {
            *sig = SO_FILESIG_NONE;
        }
    }

clean:
    so_free(&content);
    return err;
}

ErrImpl so_filesig(So path, bool *uncertain, So_Filesig_List *sig) {
    FILE *fp = so_file_fp(path, "r");
    if(!fp) return SO_FILE_ERR_INVALID;
    so_filesig_fp(fp, so_get_ext(path), uncertain, sig);
    fclose(fp);
    return 0;
}

inline void so_filesig_fmt(So *out, So_Filesig_List sig) {
    switch(sig) {
    
        case SO_FILESIG_NONE: so_extend(out, so("none")); break;
        case SO_FILESIG_SCRIPT: so_extend(out, so("script")); break;
        case SO_FILESIG_GIF: so_extend(out, so("gif")); break;
        case SO_FILESIG_TIFF: so_extend(out, so("tiff")); break;
        case SO_FILESIG_BIGTIFF: so_extend(out, so("bigtiff")); break;
        case SO_FILESIG_OPENEXR: so_extend(out, so("openexr")); break;
        case SO_FILESIG_BPG: so_extend(out, so("bpg")); break;
        case SO_FILESIG_JPEG: so_extend(out, so("jpeg")); break;
        case SO_FILESIG_JPEG2K: so_extend(out, so("jpeg2k")); break;
        case SO_FILESIG_QOI: so_extend(out, so("qoi")); break;
        case SO_FILESIG_ZIPLIKE: so_extend(out, so("ziplike")); break;
        case SO_FILESIG_RAR: so_extend(out, so("rar")); break;
        case SO_FILESIG_ELF: so_extend(out, so("elf")); break;
        case SO_FILESIG_PNG: so_extend(out, so("png")); break;
        case SO_FILESIG_HEIC: so_extend(out, so("heic")); break;
        case SO_FILESIG_PDF: so_extend(out, so("pdf")); break;
        case SO_FILESIG_OGG: so_extend(out, so("ogg")); break;
        case SO_FILESIG_WAV: so_extend(out, so("wav")); break;
        case SO_FILESIG_AVI: so_extend(out, so("avi")); break;
        case SO_FILESIG_MP3: so_extend(out, so("mp3")); break;
        case SO_FILESIG_LZH: so_extend(out, so("lzh")); break;
        case SO_FILESIG_BMP: so_extend(out, so("bmp")); break;
        case SO_FILESIG_FLAC: so_extend(out, so("flac")); break;
        case SO_FILESIG_XAR: so_extend(out, so("xar")); break;
        case SO_FILESIG_TAR: so_extend(out, so("tar")); break;
        case SO_FILESIG_TOX: so_extend(out, so("tox")); break;
        case SO_FILESIG_7Z: so_extend(out, so("7z")); break;
        case SO_FILESIG_GZ: so_extend(out, so("gz")); break;
        case SO_FILESIG_XZ: so_extend(out, so("xz")); break;
        case SO_FILESIG_LZ4: so_extend(out, so("lz4")); break;
        case SO_FILESIG_FLIF: so_extend(out, so("flif")); break;
        case SO_FILESIG_MKV: so_extend(out, so("mkv")); break;
        case SO_FILESIG_MPEG4: so_extend(out, so("mpeg4")); break;
        case SO_FILESIG_ZLIB: so_extend(out, so("zlib")); break;
        case SO_FILESIG_LZFSE: so_extend(out, so("lzfse")); break;
        case SO_FILESIG_QCOW: so_extend(out, so("qcow")); break;
        default: so_extend(out, so("other")); break;

    }
}

