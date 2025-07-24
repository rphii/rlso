#include "so.h"
#include "so-find.h"
#include "so-fx.h"

#include <unistd.h>
#include <wordexp.h>

size_t str_index_nof(So so, size_t index) {
    So_Ref ref = so_ref(so);
    size_t len_nof = 0;
    size_t n = 0, m = 0, i = 0;
    So snip = so;
    if(!index) return 0;
    for(;;) {
        snip = so_i0(so, i);
        n = so_find_f(snip, &m);
        if(len_nof + n >= index) {
            //printff("DONE %zu + %zu - %zu", i, index, len_nof);
            return i + (index - len_nof);
        }
        len_nof += n;
        i += m;
        if(i >= ref.len) break;
    }
    return ref.len;
}

size_t str_index_nof(Str str, size_t index) {
    size_t len = str_len_raw(str);
    size_t len_nof = 0;
    size_t n = 0, m = 0, i = 0;
    Str snip = str;
    if(!index) return 0;
    for(;;) {
        snip = str_i0(str, i);
        n = str_find_f(snip, &m);
        if(len_nof + n >= index) {
            //printff("DONE %zu + %zu - %zu", i, index, len_nof);
            return i + (index - len_nof);
        }
        len_nof += n;
        i += m;
        if(i >= len) break;
    }
    return str_len_raw(str);
}

void str_fmt_fgbgx(Str *out, const StrC text, Color fg, Color bg, bool bold, bool italic, bool underline, bool bashsafe) { /*{{{*/
    ASSERT_ARG(out);
    if(!str_is_dynamic(*out)) ABORT("attempting to format constant string");
    bool do_fmt = ((fg.rgba || bg.rgba || bold || italic || underline));
    if(!do_fmt) {
        str_fmt(out, "%.*s", STR_F(text));
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
    if(fg.rgba && bg.rgba) { str_fmt(out, fmt, fg.r, fg.g, fg.b, bg.r, bg.g, bg.b, STR_F(text)); }
    else if(fg.rgba) {       str_fmt(out, fmt, fg.r, fg.g, fg.b, STR_F(text)); }
    else if(bg.rgba) {       str_fmt(out, fmt, bg.r, bg.g, bg.b, STR_F(text)); }
    else {                   str_fmt(out, fmt, STR_F(text)); }
} /*}}}*/

void str_fmtx(Str *out, StrFmtX fmtx, char *fmt, ...) {
    ASSERT_ARG(out);
    ASSERT_ARG(fmt);
    //size_t len_old = out->len;
    va_list va;
    Str tmp = {0};
    va_start(va, fmt);
    str_fmt_va(&tmp, fmt, va);
    va_end(va);
    if(fmtx.nocolor && *fmtx.nocolor) {
        str_extend(out, tmp);
    } else {
        str_fmt_fgbgx(out, tmp, fmtx.fg, fmtx.bg, fmtx.bold, fmtx.italic, fmtx.underline, fmtx.bashsafe);
    }
    str_free(&tmp);
}

void str_fmt_al(Str *out, StrAlign *p, size_t i0, size_t iNL, size_t iE, char *format, ...) {
    ASSERT_ARG(out);
    ASSERT_ARG(p);
    ASSERT_ARG(p);
    if(iE <= i0) return;
    Str str = {0};
    va_list va;
    va_start(va, format);
    str_fmt_va(&str, format, va);
    va_end(va);
    /* printal */
    if(iE <= i0) return;
    bool first = true;
    size_t len = str_len_raw(str);
    size_t w = iE - i0;
    size_t w0 = iE > p->progress ? iE - p->progress : w;
    //printff("w0 %zu",w0);
    size_t pad = i0 > p->progress ? i0 - p->progress : 0;
    w0 -= pad;
    //printff(".");getchar();
    ////printff("[%.*s] progress:%zu, pad:%zu, w0:%zu i0prev:%zu i0:%zu",STR_F(str),p->progress,pad,w0,p->i0_prev,i0);
    str_fmt(out, "%*s", (int)pad, "");
    p->progress += pad;
    bool nl_pending = (i0 && p->i0_prev && i0 > p->i0_prev && p->progress > i0);
    if(nl_pending) {
        ////printff("NEWLINE!");
        str_fmt(out, "\n%*s", (int)iNL, "");
        p->progress = iNL;
        nl_pending = false;
        w0 = iE - iNL;
    }
    //bool nl_pending = false;
    //printff(".");getchar();
    for(size_t j0 = 0; j0 < len; ) {
        Str buf0 = str_i0(str, j0);
        if(str_at(buf0, 0) == '\n' || nl_pending) {
            if(!nl_pending) ++j0;
            p->progress = 0;
            str_push(out, '\n');
            ////printff("NEWLINE! [%.*s] %u", STR_F(buf0), nl_pending);
            nl_pending = false;
            continue;
        } else if(str_at(buf0, 0) == ' ' || str_at(buf0, 0) == '\t') {
            if((first && !p->progress) || !first) {
                ++j0;
                continue;
            }
        }
        Str bufws = buf0;
        if(!str_len_raw(bufws)) break;
        Str bufnl = str_iE(bufws, str_find_ch(bufws, '\n'));
        if(!bufnl.len) break;
        //printff("%p .. %p = %zu", bufws.str, str.str, bufws.str-str.str-j0);
        j0 += bufnl.str - str.str - j0;
        size_t inof = str_index_nof(bufnl, first ? w0 : w);
        size_t jE = inof < str_len_raw(bufnl) ? inof : str_len_raw(bufnl);
        Str buf = str_iE(bufws, jE);
        size_t lnof = str_len_nof(buf);
        /* get the format */
        Str fmt = {0};
        size_t x = str_rfind_f0(buf, &fmt);
        //printf("[");
        if(!first) {
            str_fmt(out, "%*s", (int)(iNL), "");
            p->progress += iNL;
        }
        str_extend(out, p->fmt);
        str_extend(out, buf);
        ////printff("BUF[%.*s]%u:%zu:%zu %zu:%zu:%zu", STR_F(buf), first, w0, w, i0,iNL,iE);
        if(str_len_raw(fmt) || str_len_raw(p->fmt)) str_extend(out, str("\033[0m"));
        //printf("]");
        p->progress += lnof;
        if(p->progress >= iE) {
            nl_pending = true;
        }
        if(x < str_len_raw(buf)) {
            p->fmt = fmt;
        }
        j0 += jE;
        first = false;
        w = iE - iNL;
    }
    if(nl_pending) {
        p->progress = 0;
        str_push(out, '\n');
        printff("NEWLINE!");
    }
    /* done */
    str_free(&str);
    p->i0_prev = i0;
}

