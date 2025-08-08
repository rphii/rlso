#include "so-core.h"
#include "so-find.h"
#include "so-split.h"
#include "so-fx.h"
#include "so-cmp.h"
#include "so-print.h"

#include <stdlib.h>
#include <rlc/err.h>

#include <unistd.h>
#include <wordexp.h>

size_t so_len_nfx(So str) { /*{{{*/
    So snip = str;
    So pat = so("\033[");
    size_t len_nof = str.len;
    while(so_len(snip)) {
        ASSERT_ARG(so_len(snip));
        So right, left = so_split_sub(snip, pat, &right, SO_CMP);
        if(so_len(right)) {
            so_split_ch(right, 'm', &snip);
            size_t gap = so_it0(snip) - so_itE(left);
            len_nof -= gap;
        } else {
            snip = right;
        }
    }
    return len_nof;
} /*}}}*/


size_t so_nfx_index(So so, size_t index) {
    So ref = so;
    size_t len_nof = 0;
    size_t n = 0, m = 0, i = 0;
    So snip = so;
    if(!index) return 0;
    for(;;) {
        snip = so_i0(so, i);
        n = so_find_f(snip, &m);
        if(len_nof + n >= index) {
            return i + (index - len_nof);
        }
        len_nof += n;
        i += m;
        if(i >= ref.len) break;
    }
    return ref.len;
}

void so_extend_fgbgx(So *out, Color fg, Color bg, bool bold, bool italic, bool underline, bool bashsafe, So add) {
    ASSERT_ARG(out);
    bool do_fmt = ((fg.rgba || bg.rgba || bold || italic || underline));
    if(!do_fmt) {
        so_extend(out, add);
    } else {
        char cfmt[64] = {0}; /* theoretically 52 would be enough? */
        int len = sizeof(cfmt)/sizeof(*cfmt);
        int offs = 0;
        offs += snprintf(cfmt, len, "%s%s", bashsafe ? "\\[" : "", FS_BEG);
        if(fg.rgba) offs += snprintf(cfmt + offs, len - offs, "%s", FS_FG3);
        if(bg.rgba) offs += snprintf(cfmt + offs, len - offs, "%s", FS_BG3);
        if(bold) offs += snprintf(cfmt + offs, len - offs, "%s", BOLD);
        if(italic) offs += snprintf(cfmt + offs, len - offs, "%s", IT);
        if(underline) offs += snprintf(cfmt + offs, len - offs, "%s", UL);
        snprintf(cfmt + offs, len - offs, "%s", bashsafe ? "m\\]%.*s\\[\033[0m\\]" : FS_END);
        //printff(">>CFMT[%s]+TMP[%.*s]",cfmt,SO_F(tmp));
        if(fg.rgba && bg.rgba) { so_fmt(out, cfmt, fg.r, fg.g, fg.b, bg.r, bg.g, bg.b, SO_F(add)); }
        else if(fg.rgba) {       so_fmt(out, cfmt, fg.r, fg.g, fg.b, SO_F(add)); }
        else if(bg.rgba) {       so_fmt(out, cfmt, bg.r, bg.g, bg.b, SO_F(add)); }
        else {                   so_fmt(out, cfmt, SO_F(add)); }
    }
} /*}}}*/


void so_fmt_fgbgx(So *out, Color fg, Color bg, bool bold, bool italic, bool underline, bool bashsafe, char *fmt, ...) {
    ASSERT_ARG(out);
    So tmp = {0};
    va_list va;
    va_start(va, fmt);
    so_fmt_va(&tmp, fmt, va);
    va_end(va);
    so_extend_fgbgx(out, fg, bg, bold, italic, underline, bashsafe, tmp);
} /*}}}*/

void so_fmt_fx(So *out, So_Fx fx, size_t i0_override, char *fmt, ...) {
    ASSERT_ARG(out);
    ASSERT_ARG(fmt);
    //size_t len_old = out->len;
    So str = {0};
    So str2 = {0};
    va_list va;
    va_start(va, fmt);
    so_fmt_va(&str, fmt, va);
    va_end(va);
    if(fx.nocolor && *fx.nocolor) {
        so_extend(&str2, str);
    } else {
        so_extend_fgbgx(&str2, fx.fg, fx.bg, fx.bold, fx.italic, fx.underline, fx.bashsafe, str);
    }
    so_extend_al(out, fx.align, i0_override, str2);
    so_free(&str);
    so_free(&str2);
}

void so_fmt_websafe(So *out, So text) { /*{{{*/
    So escape = so(" <>#%+{}|\\^~[]';/?:@=&$");
    for(size_t i = 0; i < so_len(text); ++i) {
        unsigned char c = so_at(text, i);
        if(so_find_ch(escape, c) < so_len(escape)) {
            so_fmt(out, "%%%02x", c);
        } else {
            so_push(out, c);
        }
    }
} /*}}}*/

