#include "so-base64.h"
#include <rlc/err.h>

char so_ch_as_base64(unsigned char c, char c62, char c63);
char so_ch_un_base64(unsigned char c, char c62, char c63);

inline char so_ch_as_base64(unsigned char c, char c62, char c63) {
    if(c <= 25) return c + 'A';
    if(c <= 51) return c - 26 + 'a';
    if(c <= 61) return c - 52 + '0';
    if(c == 62) return c62;
    if(c == 63) return c63;
    ABORT("invalid base64 as-code: %u", c);
}

inline char so_ch_un_base64(unsigned char c, char c62, char c63) {
    if(c >= 'A' && c <= 'Z') return c - 'A';
    if(c >= 'a' && c <= 'z') return c - 'a' + 26;
    if(c >= '0' && c <= '9') return c - '0' + 52;
    if(c == c62) return 62;
    if(c == c63) return 63;
    ABORT("invalid base64 un-code: %u", c);
}

inline void so_base64_fmt_encode(So *out, So in) {
    so_base64_fmt_encode_ext(out, in, '+', '/', '=');
}

inline void so_base64_fmt_encode_ext(So *out, So in, char c62, char c63, char cpad) {
    size_t len = so_len(in);
    size_t pad = len % 3 ? 3 - len % 3 : 0;
    unsigned int j = 0;
    char cl = 0;
    for(size_t i = 0; i < len; ++i) {
        char cr = so_at(in, i);
        j = i % 3;
        switch(j) {
            case 0: {
                unsigned char b = (cr & 0xFC) >> 2;
                so_push(out, so_ch_as_base64(b, c62, c63));
            } break;
            case 1: {
                unsigned char bl = (cl & 0x03) << 4;
                unsigned char br = (cr & 0xF0) >> 4;
                unsigned char b = bl | br;
                so_push(out, so_ch_as_base64(b, c62, c63));
            } break;
            case 2: {
                unsigned char bl = (cl & 0x0F) << 2;
                unsigned char br = (cr & 0xC0) >> 6;
                unsigned char b = bl | br;
                so_push(out, so_ch_as_base64(b, c62, c63));

                unsigned char d = (cr & 0x3F);
                so_push(out, so_ch_as_base64(d, c62, c63));
            } break;
            default: ABORT("unreachable code");
        }
        cl = cr;
    }
    if(pad == 1) {
        unsigned char b = (cl & 0x0F) << 2;
        so_push(out, so_ch_as_base64(b, c62, c63));
        so_push(out, cpad);
    } else if(pad == 2) {
        unsigned char b = (cl & 0x03) << 4;
        so_push(out, so_ch_as_base64(b, c62, c63));
        so_push(out, cpad);
        so_push(out, cpad);
    } else if(pad) ABORT("unreachable code");
}

inline int so_base64_fmt_decode_ext(So *out, So in_base64, char c62, char c63, char pad) {
    size_t len = so_len(in_base64);
    if(len % 4) return 1;
    for(size_t i = 0; i < len; i += 4) {
        unsigned char b0 = so_at(in_base64, i + 0);
        unsigned char b1 = so_at(in_base64, i + 1);
        unsigned char b2 = so_at(in_base64, i + 2);
        unsigned char b3 = so_at(in_base64, i + 3);
        unsigned char c0 = so_ch_un_base64(b0, c62, c63);
        unsigned char c1 = so_ch_un_base64(b1, c62, c63);
        unsigned char c2 = b2 != pad ? so_ch_un_base64(b2, c62, c63) : 0;
        unsigned char c3 = b3 != pad ? so_ch_un_base64(b3, c62, c63) : 0;
        printff("%u %u %u %u",c0,c1,c2,c3);
        unsigned char d0 = (c0 << 2) | (c1 >> 4);
        unsigned char d1 = (c1 << 4) | (c2 >> 2);
        unsigned char d2 = (c2 << 6) | (c3 >> 0);
        so_push(out, d0);
        if(b2 != pad) so_push(out, d1);
        if(b3 != pad) so_push(out, d2);
    }
    return 0;
}

inline int so_base64_fmt_decode(So *out, So in_base64) {
    int result = so_base64_fmt_decode_ext(out, in_base64, '+', '/', '=');
    return result;
}


