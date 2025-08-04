#include "so-core.h"
#include "so-align.h"
#include "so-find.h"
#include "so-fx.h"
#include "so-print.h"

#include <rl/err.h>

void so_extend_al(So *out, So_Align *p, So add) {
    ASSERT_ARG(out);
    ASSERT_ARG(p);
    ASSERT_ARG(p);
    size_t iE = p->iE;
    size_t i0 = p->i0;
    size_t iNL = p->iNL;
    if(iE <= i0) return;
    /* printal */
    if(iE <= i0) return;
    bool first = true;
    size_t len = so_len(add);
    size_t w = iE - i0;
    size_t w0 = iE > p->progress ? iE - p->progress : w;
    ////printff("w0 %zu",w0);
    size_t pad = i0 > p->progress ? i0 - p->progress : 0;
    w0 -= pad;
    //printff(".");getchar();
    ////printff("[%.*s] progress:%zu, pad:%zu, w0:%zu i0prev:%zu i0:%zu",SO_F(add),p->progress,pad,w0,p->i0_prev,i0);
    so_fmt(out, "%*s", (int)pad, "");
    p->progress += pad;
    bool nl_pending = (i0 && p->i0_prev && i0 > p->i0_prev && p->progress > i0);
    if(nl_pending) {
        ////printff("NEWLINE!");
        so_fmt(out, "\n%*s", (int)iNL, "");
        p->progress = iNL;
        nl_pending = false;
        w0 = iE - iNL;
    }
    //bool nl_pending = false;
    //printff(".");getchar();
    for(size_t j0 = 0; j0 < len; ) {
        So buf0 = so_i0(add, j0);
        if(so_at(buf0, 0) == '\n' || nl_pending) {
            if(!nl_pending) ++j0;
            p->progress = 0;
            so_push(out, '\n');
            ////printff("NEWLINE! [%.*s] %u", SO_F(buf0), nl_pending);
            nl_pending = false;
            continue;
        } else if(so_at(buf0, 0) == ' ' || so_at(buf0, 0) == '\t') {
            if((first && !p->progress) || !first) {
                ++j0;
                continue;
            }
        }
        So bufws = buf0;
        if(!so_len(bufws)) break;
        So bufnl = so_iE(bufws, so_find_ch(bufws, '\n'));
        if(!so_len(bufnl)) break;
        //printff("%p .. %p = %zu", bufws.str, add.str, bufws.str-add.str-j0);
        j0 += so_it0(bufnl) - so_it0(add) - j0;
        size_t inof = so_nfx_index(bufnl, first ? w0 : w);
        size_t jE = inof < so_len(bufnl) ? inof : so_len(bufnl);
        So buf = so_iE(bufws, jE);
        size_t lnof = so_len_nfx(buf);
        /* get the format */
        So fmt = {0};
        size_t x = so_rfind_f0(buf, &fmt);
        //printf("[");
        if(!first) {
            so_fmt(out, "%*s", (int)(iNL), "");
            p->progress += iNL;
        }
        //printff(">>EXT FMT vvv");
        //so_printdbg(p->fmt);
        so_extend(out, p->fmt);
        //printff(">>EXT BUF[%.*s]",SO_F(buf));
        so_extend(out, buf);
        ////printff("BUF[%.*s]%u:%zu:%zu %zu:%zu:%zu", SO_F(buf), first, w0, w, i0,iNL,iE);
        if(so_len(fmt) || so_len(p->fmt)) so_extend(out, so("\033[0m"));
        //printf("]");
        ////printff("p->progress %zu += lnof %zu", p->progress, lnof);
        p->progress += lnof;
        if(p->progress >= iE) {
            nl_pending = true;
        }
        if(x < so_len(buf)) {
            so_copy(&p->fmt, fmt);
        }
        j0 += jE;
        first = false;
        w = iE - iNL;
    }
    if(nl_pending) {
        p->progress = 0;
        so_push(out, '\n');
        ////printff("NEWLINE!");
    }
    /* done */
    p->i0_prev = i0;
}


void so_fmt_al(So *out, So_Align *p, char *format, ...) {
    ASSERT_ARG(out);
    ASSERT_ARG(p);
    ASSERT_ARG(p);
    size_t iE = p->iE;
    size_t i0 = p->i0;
    size_t iNL = p->iNL;
    if(iE <= i0) return;
    So tmp = {0};
    va_list va;
    va_start(va, format);
    so_fmt_va(&tmp, format, va);
    va_end(va);
    so_extend_al(out, p, tmp);
    /* done */
    so_free(&tmp);
    p->i0_prev = i0;
}

void so_al_rewind(So_Align *al) {
    ASSERT_ARG(al);
    al->i0_prev = 0;
    al->progress = 0;
    so_clear(&al->fmt);
}

void so_al_clear(So_Align *al) {
    ASSERT_ARG(al);
    so_al_rewind(al);
    so_clear(&al->fmt);
}

void so_al_free(So_Align *al) {
    ASSERT_ARG(al);
    so_free(&al->fmt);
    memset(al, 0, sizeof(*al));
}


