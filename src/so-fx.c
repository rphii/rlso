#include "so.h"
#include "so-find.h"
#include "so-fx.h"
#include "so-cmp.h"

#include <stdlib.h>
#include <rl/err.h>

#include <unistd.h>
#include <wordexp.h>

size_t so_len_nfx(So str) { /*{{{*/
    size_t len = so_len(str), n = 0, m = 0;
    So snip = so_ll(so_it0(str), len);
    So pat = so("\033[");
    bool count = true;
    size_t len_nof = 0;
    for(size_t i = 0; i < len; ++i) {
        //printff("i %zu, so_len %zu", i, so_len(snip));
        ASSERT_ARG(so_len(snip));
        if(!count) {
            if(so_at(snip, 0) == 'm') {
                count = true;
            }
        } else {
            ++len_nof;
            if(!so_cmp0(snip, pat)) {
                count = false;
            }
        }
        //printff("SNIP %.*s", SO_F(snip));
        snip = so_i0(snip, 1);
    }
    return len_nof;
    printff(" LEN IS %zu",len);
    return len;
} /*}}}*/


size_t so_nfx_index(So so, size_t index) {
    So_Ref ref = so_ref(so);
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

void so_fmt_fgbgx(So *out, So text, Color fg, Color bg, bool bold, bool italic, bool underline, bool bashsafe) { /*{{{*/
    ASSERT_ARG(out);
    bool do_fmt = ((fg.rgba || bg.rgba || bold || italic || underline));
    if(!do_fmt) {
        so_fmt(out, "%.*s", SO_F(text));
        return;
    }
    char fmt[64] = {0}; /* theoretically 52 would be enough? */
    int len = sizeof(fmt)/sizeof(*fmt);
    int offs = 0;
    offs += snprintf(fmt, len, "%s%s", bashsafe ? "\\[" : "", FS_BEG);
    if(fg.rgba) offs += snprintf(fmt + offs, len - offs, "%s", FS_FG3);
    if(bg.rgba) offs += snprintf(fmt + offs, len - offs, "%s", FS_BG3);
    if(bold) offs += snprintf(fmt + offs, len - offs, "%s", BOLD);
    if(italic) offs += snprintf(fmt + offs, len - offs, "%s", IT);
    if(underline) offs += snprintf(fmt + offs, len - offs, "%s", UL);
    snprintf(fmt + offs, len - offs, "%s", bashsafe ? "m\\]%.*s\\[\033[0m\\]" : FS_END);
    if(fg.rgba && bg.rgba) { so_fmt(out, fmt, fg.r, fg.g, fg.b, bg.r, bg.g, bg.b, SO_F(text)); }
    else if(fg.rgba) {       so_fmt(out, fmt, fg.r, fg.g, fg.b, SO_F(text)); }
    else if(bg.rgba) {       so_fmt(out, fmt, bg.r, bg.g, bg.b, SO_F(text)); }
    else {                   so_fmt(out, fmt, SO_F(text)); }
} /*}}}*/

void so_fmt_fx(So *out, So_Fx fx, char *fmt, ...) {
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
        so_fmt_fgbgx(&str2, str, fx.fg, fx.bg, fx.bold, fx.italic, fx.underline, fx.bashsafe);
    }
    //so_1buf_old(out, &onebuf);
    //so_1buf_new(out, &onebuf);
    if(fx.align) {
        //so_1buf_old(out, &onebuf);
        so_fmt_al(out, fx.align, "%.*s", SO_F(str2));
        //so_1buf_new(out, &onebuf);
    }
    so_free(&str);
    so_free(&str2);
}

