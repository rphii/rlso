#include "so.h"
#include "so-uc.h"

ErrDecl so_uc_point(So so, So_Uc_Point *point) {
    ASSERT_ARG(point); /* LCOV_EXCL_LINE */
    So_Uc_Point tinker = {0};
    // figure out how many bytes we need
    if((*so.str & 0x80) == 0) point->bytes = 1;
    else if((*so.str & 0xE0) == 0xC0) point->bytes = 2;
    else if((*so.str & 0xF0) == 0xE0) point->bytes = 3;
    else if((*so.str & 0xF8) == 0xF0) point->bytes = 4;
    else if((*so.str & 0xFC) == 0xF8) point->bytes = 5;
    else if((*so.str & 0xFE) == 0xFC) point->bytes = 6;
    else return -1; //THROW("unknown utf-8 pattern [%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x]", (unsigned char )so.str[0], (unsigned char )so.str[1], (unsigned char )so.str[2], (unsigned char )so.str[3], (unsigned char )so.str[4], (unsigned char )so.str[5], (unsigned char )so.str[6], (unsigned char )so.str[7]);
    // magical mask shifting
    size_t shift = (point->bytes - 1) * 6;
    int mask = 0x7F;
    if(so.len < point->bytes) return -1;
    if(point->bytes > 1) mask >>= point->bytes;
    // extract info from bytes
    for(int i = 0; i < point->bytes; i++) {
        // add number to point
        if(!so.str[i]) return -1; // THROW(ERR_CSTR_INVALID);
        tinker.val |= (uint32_t)((so.str[i] & mask) << shift);
        if(mask == 0x3F) {
            if((unsigned char)(so.str[i] & ~mask) != 0x80) {
                return -1; //THROW("encountered invalid bytes in utf-8 sequence");
                point->bytes = 0;
                break;
            }
        }
        // adjust shift amount
        shift -= 6;
        // update mask
        mask = 0x3F;
    }
    // one final check, unicode doesn't go that far, wth unicode, TODO check ?!
    /////if(tinker.val > 0x10FFFF || !point->bytes) {
    /////    point->val = (unsigned char)*so.str;
    /////    point->bytes = 1;
    /////} else {
        point->val = tinker.val;
    /////}
    return 0;
}

ErrDecl so_uc_fmt_point(So *out, So_Uc_Point *point) {
    ASSERT_ARG(out);
    ASSERT_ARG(point);
    int bytes = 0;
    int shift = 0;  // shift in bits
    uint32_t in = point->val;
    // figure out how many bytes we need
    if(in < 0x0080) bytes = 1;
    else if(in < 0x0800) bytes = 2;
    else if(in < 0x10000) bytes = 3;
    else if(in < 0x200000) bytes = 4;
    else if(in < 0x4000000) bytes = 5;
    else if(in < 0x80000000) bytes = 6;
    else return -1;
    shift = (bytes - 1) * 6;
    uint32_t mask = 0x7F;
    if(bytes > 1) mask >>= bytes;
    // create bytes
    for(int i = 0; i < bytes; i++) {
        // add actual character coding
        char c = ((in >> shift) & mask);;
        // add first byte code
        if(!i && bytes > 1) {
            c |= (char)(((uint32_t)~0 << (8 - bytes)) & 0xFF);
        }
        // add any other code
        if(i) {
            c |= (char)0x80;
        }
        // adjust shift and reset mask
        shift -= 6;
        mask = 0x3F;
        so_push(out, c);
    }
    point->bytes = bytes;
    return 0;
}

