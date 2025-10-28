#ifndef RLSO_BASE64

#include "so-core.h"

void so_base64_fmt_encode(So *out, So in);
void so_base64_fmt_encode_ext(So *out, So in, char c62, char c63, char cpad);

int so_base64_fmt_decode_ext(So *out, So in_base64, char c62, char c63, char pad);
int so_base64_fmt_decode(So *out, So in_base64);

#define RLSO_BASE64
#endif // RLSO_BASE64

