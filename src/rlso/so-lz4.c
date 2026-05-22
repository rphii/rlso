#include <rlc.h>
#include "so-lz4.h"
#include "so-core.h"

#if RLSO_USE_LZ4

#include <lz4frame.h>

ErrDecl so_lz4_compress(So *out_ext, So in) {

    const char* data_in = in.str;
    size_t data_size = in.len;

    size_t max_compressed_size = LZ4F_compressFrameBound(data_size, NULL);
    size_t out_len = out_ext->len;
    so_clear(out_ext);
    so_resize(out_ext, out_len + max_compressed_size);
    char *compressed = out_ext->str + out_len;

    size_t compressed_size = LZ4F_compressFrame(compressed, max_compressed_size, data_in, data_size, NULL);

    if (LZ4F_isError(compressed_size)) {
        fprintf(stderr, "%s: Compression failed: %s\n", __func__, LZ4F_getErrorName(compressed_size));
        return 1;
    }

    out_ext->len = out_len + compressed_size;
    return 0;
}

ErrDecl so_lz4_decompress(So *out_ext, So in) {
    size_t err = 0;

    size_t size_header = LZ4F_headerSize(in.str, in.len);
    if(LZ4F_isError(size_header)) {
        //printff("Invalid LZ4 frame header: %zu", size_header);
        return -1;
    }

    LZ4F_dctx *dctx = NULL;
    if((err = LZ4F_createDecompressionContext(&dctx, LZ4F_VERSION))) {
        //printff("Failed to create context: %zu", err);
        return -1;
    }

    size_t in_pos = 0;
    uint8_t out_buf[4096];

    while(in_pos < in.len) {
        size_t in_len = in.len - in_pos;
        size_t out_len = 4096;

        err = LZ4F_decompress(dctx, out_buf, &out_len, (uint8_t *)in.str + in_pos, &in_len, NULL);

        if(LZ4F_isError(err)) {
            //printff("Decompression error");
            goto clean;
        }

        so_extend(out_ext, so_ll((char *)out_buf, out_len));

        in_pos += in_len;
        if(err == 0) break; // Frame complete
    }

clean:
    LZ4F_freeDecompressionContext(dctx);
    return 0;
}

#else /* RLSO_USE_LZ4 */

ErrDecl so_lz4_compress(So *out, So in) {
    ABORT("feature is not compiled into the library");
    return -1;
}

ErrDecl so_lz4_decompress(So *out, So in) {
    ABORT("feature is not compiled into the library");
    return -1;
}


#endif /* RLSO_USE_LZ4 */


