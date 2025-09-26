#include "so-core.h"
#include "so-align.h"
#include "so-find.h"
#include "so-fx.h"
#include "so-print.h"

#include <rlc.h>

void so_extend_al(So *out, So_Align al, size_t i0_override, So add) {
    ASSERT_ARG(out);
    //printff("CACHE i0prev %zu prog %zu lines %zu",al.cache->i0_prev,al.cache->progress,al.cache->lines_done);
    if(!al.cache) {
        so_extend(out, add);
        return;
    }
    const size_t iE = al.iE;
    const size_t i0 = i0_override ? i0_override : al.i0;
    const size_t iNL = al.iNL;
    if(iE <= i0) return;
    /* printal */
    if(iE <= i0) return;
    if(al.n_lines && al.cache->lines_done >= al.n_lines) return;
    bool first = true;
    size_t len = so_len(add);
    size_t w = iE - i0;
    size_t w0 = iE > al.cache->progress ? iE - al.cache->progress : w;
    ////printff("w0 %zu",w0);
    size_t pad = i0 > al.cache->progress ? i0 - al.cache->progress : 0;
    w0 -= pad;
    //printff(".");getchar();
    //printff("[%.*s] progress:%zu, pad:%zu, w0:%zu i0prev:%zu i0:%zu",SO_F(add),al.cache->progress,pad,w0,al.cache->i0_prev,i0);
    so_fmt(out, "%*s", (int)pad, "");
    al.cache->progress += pad;
    bool nl_pending = (i0 && al.cache->i0_prev && i0 > al.cache->i0_prev && al.cache->progress > i0);
    if(nl_pending) {
        ////printff("NEWLINE!");
        so_fmt(out, "\n%*s", (int)iNL, "");
        al.cache->progress = iNL;
        ++al.cache->lines_done;
        nl_pending = false;
        w0 = iE - iNL;
    }
    //bool nl_pending = false;
    //printff(".");getchar();
    for(size_t j0 = 0; j0 < len; ) {
        if(al.n_lines && al.cache->lines_done >= al.n_lines) {
            break;
        }
        So buf0 = so_i0(add, j0);
        if(so_at0(buf0) == '\n' || nl_pending) {
            if(!nl_pending) ++j0;
            al.cache->progress = 0;
            so_push(out, '\n');
            ++al.cache->lines_done;
            ////printff("NEWLINE! [%.*s] %u", SO_F(buf0), nl_pending);
            nl_pending = false;
            continue;
        } else if(al.cache->lines_done && (so_at(buf0, 0) == ' ' || so_at(buf0, 0) == '\t')) {
            if((first && !al.cache->progress) || !first) {
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
            al.cache->progress += iNL;
        }
        //printff(">>EXT FMT vvv");
        //so_printdbg(al.cache->fmt);
        so_extend(out, al.cache->fmt);
        //printff(">>EXT BUF[%.*s]",SO_F(buf));
        so_extend(out, buf);
        ////printff("BUF[%.*s]%u:%zu:%zu %zu:%zu:%zu", SO_F(buf), first, w0, w, i0,iNL,iE);
        if(so_len(fmt) || so_len(al.cache->fmt)) so_extend(out, so("\033[0m"));
        //printf("]");
        ////printff("al->progress %zu += lnof %zu", al->progress, lnof);
        al.cache->progress += lnof;
        if(al.cache->progress >= iE) {
            if(al.n_lines && al.cache->lines_done + 1 >= al.n_lines) {
                ++al.cache->lines_done;
                break;
            }
            nl_pending = true;
        }
        if(x < so_len(buf)) {
            so_copy(&al.cache->fmt, fmt);
        }
        j0 += jE;
        first = false;
        if(iNL >= iE) break;
        w = iE - iNL;
    }
    if(nl_pending) {
        al.cache->progress = 0;
        so_push(out, '\n');
        ++al.cache->lines_done;
        ////printff("NEWLINE!");
    }
    /* done */
    al.cache->i0_prev = i0;
    //so_clear(&al.cache->fmt);
}

void so_al_nl(So *out, So_Align al, int nl) {
    while(nl) {
        so_fmt_al(out, al, 0, "\n");
        --nl;
    }
}


void so_fmt_al(So *out, So_Align al, size_t i0_override, char *format, ...) {
    ASSERT_ARG(out);
    So tmp = {0};
    va_list va;
    va_start(va, format);
    so_fmt_va(&tmp, format, va);
    va_end(va);
    so_extend_al(out, al, i0_override, tmp);
    /* done */
    so_free(&tmp);
}

void so_al_config(So_Align *al, size_t i0, size_t iNL, size_t iE, size_t n_lines, So_Align_Cache *cache) {
    al->i0 = i0;
    al->iE = iE;
    al->iNL = iNL;
    al->n_lines = n_lines;
    if(cache) {
        al->cache = cache;
    }
}

void so_al_cache_rewind(So_Align_Cache *c) {
    ASSERT_ARG(c);
    c->i0_prev = 0;
    c->progress = 0;
    c->lines_done = 0;
    so_clear(&c->fmt);
}

void so_al_cache_clear(So_Align_Cache *c) {
    ASSERT_ARG(c);
    so_al_cache_rewind(c);
    so_clear(&c->fmt);
}

void so_al_cache_free(So_Align_Cache *c) {
    ASSERT_ARG(c);
    so_free(&c->fmt);
    memset(c, 0, sizeof(*c));
}


