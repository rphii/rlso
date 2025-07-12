#include "so-cmp.h"
#include "so.h"
#include <string.h>
#include <ctype.h>

/* internal use {{{ */

static inline int so_cmp_len(char *a, size_t la, char *b, size_t lb);
static inline int so_cmp_s_len(char *a, size_t la, char *b, size_t lb);
static inline int so_cmp_c_len(char *a, size_t la, char *b, size_t lb);
static inline int so_cmp_cs_len(char *a, size_t la, char *b, size_t lb);

static inline int so_cmp_len(char *a, size_t la, char *b, size_t lb) {
    int result;
    if(la != lb) result = la - lb;
    else result = memcmp(a, b, la);
    return result;
}

static inline int so_cmp_s_len(char *a, size_t la, char *b, size_t lb) {
    int result;
    if(la != lb) {
        size_t less = la < lb ? la : lb;
        result = memcmp(a, b, less);
        if(!result) {
            result = la - lb;
        }
    } else {
        result = memcmp(a, b, la);
    }
    return result;
}

static inline int so_cmp_c_len(char *a, size_t la, char *b, size_t lb) {
    if(la != lb) return la - lb;
    for(size_t i = 0; i < la; ++i) {
        char ca = a[i];
        char cb = b[i];
        if(tolower((int)ca) != tolower((int)cb)) return ca - cb;
    }
    return 0;
}

static inline int so_cmp_cs_len(char *a, size_t la, char *b, size_t lb) {
    int result;
    size_t less;
    if(la != lb) less = la < lb ? la : lb;
    else less = la;
    for(size_t i = 0; i < less; ++i) {
        char ca = a[i];
        char cb = b[i];
        if(tolower((int)ca) != tolower((int)cb)) return ca - cb;
    }
    return 0;
}

/* }}} */

/* compare {{{ */

int so_cmp(So a, So b) {
    return so_cmp_len(so_it0(a), so_len(a), so_it0(b), so_len(b));
}

int so_cmp_s(So a, So b) {
    return so_cmp_s_len(so_it0(a), so_len(a), so_it0(b), so_len(b));
}

int so_cmp_c(So a, So b) {
    return so_cmp_c_len(so_it0(a), so_len(a), so_it0(b), so_len(b));
}

int so_cmp_cs(So a, So b) {
    return so_cmp_cs_len(so_it0(a), so_len(a), so_it0(b), so_len(b));
}

int so_cmp_p(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    return so_cmp_len(_so_it0(a), _so_len(a), _so_it0(b), _so_len(b));
}

int so_cmp_sp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    return so_cmp_s_len(_so_it0(a), _so_len(a), _so_it0(b), _so_len(b));
}

int so_cmp_cp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    return so_cmp_c_len(_so_it0(a), _so_len(a), _so_it0(b), _so_len(b));
}

int so_cmp_csp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    return so_cmp_cs_len(_so_it0(a), _so_len(a), _so_it0(b), _so_len(b));
}

/*}}}*/

/* compare begin {{{ */

int so_cmp0(So a, So b) {
    size_t la = so_len(a);
    size_t lb = so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_len(so_it0(a), lb, so_it0(b), lb);
}

int so_cmp0_c(So a, So b) {
    size_t la = so_len(a);
    size_t lb = so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_c_len(so_it0(a), lb, so_it0(b), lb);
}

int so_cmp0_s(So a, So b) {
    size_t la = so_len(a);
    size_t lb = so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_c_len(so_it0(a), lb, so_it0(b), lb);
}

int so_cmp0_cs(So a, So b) {
    size_t la = so_len(a);
    size_t lb = so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_cs_len(so_it0(a), lb, so_it0(b), lb);
}

int so_cmp0_p(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    size_t la = _so_len(a);
    size_t lb = _so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_len(_so_it0(a), lb, _so_it0(b), lb);
}

int so_cmp0_sp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    size_t la = _so_len(a);
    size_t lb = _so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_s_len(_so_it0(a), lb, _so_it0(b), lb);
}

int so_cmp0_cp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    size_t la = _so_len(a);
    size_t lb = _so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_c_len(_so_it0(a), lb, _so_it0(b), lb);
}

int so_cmp0_csp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    size_t la = _so_len(a);
    size_t lb = _so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_cs_len(_so_it0(a), lb, _so_it0(b), lb);
}

/*}}}*/

/* compare end {{{ */

int so_cmpE(So a, So b) {
    size_t la = so_len(a);
    size_t lb = so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_len(so_it(a, la - lb), lb, so_it0(b), lb);
}

int so_cmpE_c(So a, So b) {
    size_t la = so_len(a);
    size_t lb = so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_c_len(so_it(a, la - lb), lb, so_it0(b), lb);
}

int so_cmpE_s(So a, So b) {
    size_t la = so_len(a);
    size_t lb = so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_s_len(so_it(a, la - lb), lb, so_it0(b), lb);
}

int so_cmpE_cs(So a, So b) {
    size_t la = so_len(a);
    size_t lb = so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_cs_len(so_it(a, la - lb), lb, so_it0(b), lb);
}

int so_cmpE_p(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    size_t la = _so_len(a);
    size_t lb = _so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_len(_so_it(a, la - lb), lb, _so_it0(b), lb);
}

int so_cmpE_cp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    size_t la = _so_len(a);
    size_t lb = _so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_c_len(_so_it(a, la - lb), lb, _so_it0(b), lb);
}

int so_cmpE_sp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    size_t la = _so_len(a);
    size_t lb = _so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_s_len(_so_it(a, la - lb), lb, _so_it0(b), lb);
}

int so_cmpE_csp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    size_t la = _so_len(a);
    size_t lb = _so_len(b);
    if(la < lb) return la - lb;
    return so_cmp_cs_len(_so_it(a, la - lb), lb, _so_it0(b), lb);
}

/*}}}*/


int so_cmpx(So a, So b, So_Cmp_Attr attr) {
    if( (attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE) &&  (attr & SO_CMP_BEGIN) && !(attr & SO_CMP_END)) return so_cmp0_cs(a, b);
    if(!(attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE) &&  (attr & SO_CMP_BEGIN) && !(attr & SO_CMP_END)) return so_cmp0_s(a, b);
    if( (attr & SO_CMP_CASE_INSENSITIVE) && !(attr & SO_CMP_SORTABLE) &&  (attr & SO_CMP_BEGIN) && !(attr & SO_CMP_END)) return so_cmp0_c(a, b);
    if(!(attr & SO_CMP_CASE_INSENSITIVE) && !(attr & SO_CMP_SORTABLE) &&  (attr & SO_CMP_BEGIN) && !(attr & SO_CMP_END)) return so_cmp0(a, b);
    if( (attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE) && !(attr & SO_CMP_BEGIN) &&  (attr & SO_CMP_END)) return so_cmpE_cs(a, b);
    if(!(attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE) && !(attr & SO_CMP_BEGIN) &&  (attr & SO_CMP_END)) return so_cmpE_s(a, b);
    if( (attr & SO_CMP_CASE_INSENSITIVE) && !(attr & SO_CMP_SORTABLE) && !(attr & SO_CMP_BEGIN) &&  (attr & SO_CMP_END)) return so_cmpE_c(a, b);
    if(!(attr & SO_CMP_CASE_INSENSITIVE) && !(attr & SO_CMP_SORTABLE) && !(attr & SO_CMP_BEGIN) &&  (attr & SO_CMP_END)) return so_cmpE(a, b);
    if( (attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE) && !(attr & SO_CMP_BEGIN) && !(attr & SO_CMP_END)) return so_cmp_cs(a, b);
    if(!(attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE) && !(attr & SO_CMP_BEGIN) && !(attr & SO_CMP_END)) return so_cmp_s(a, b);
    if( (attr & SO_CMP_CASE_INSENSITIVE) && !(attr & SO_CMP_SORTABLE) && !(attr & SO_CMP_BEGIN) && !(attr & SO_CMP_END)) return so_cmp_c(a, b);
    return so_cmp(a, b);
}

int so_cmpx_p(So *a, So *b, So_Cmp_Attr attr) {
    if(!a && !b) return 0;
    if(!a || !b) return a - b;
    return so_cmpx(*a, *b, attr);
}


