#ifndef RLSO_LZ4_H
#include <lz4frame.h>
#include <rlc.h>
#include "so-core.h"

ErrDecl so_lz4_compress(So *out, So in);
ErrDecl so_lz4_decompress(So *out, So in);

#define RLSO_LZ4_H
#endif /* RLSO_LZ4_H */

