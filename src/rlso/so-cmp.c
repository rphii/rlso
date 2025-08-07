#include "so-cmp.h"
#include "so-core.h"
#include <string.h>
#include <ctype.h>
#include<stdio.h>

/* internal use {{{ */

int so_cmp(So a, So b) {
    int result;
    //printf("CMP:%.*s:%zu\n    %.*s:%zu\n", a.len, a.str,a.len, b.len, b.str,b.len);
    if(a.len != b.len) result = a.len - b.len;
    else result = memcmp(a.str, b.str, a.len);
    return result;
}

int so_cmp_s(So a, So b) {
    int result;
    if(a.len != b.len) {
        size_t less = a.len < b.len ? a.len : b.len;
        result = memcmp(a.str, b.str, less);
        if(!result) {
            result = a.len - b.len;
        }
    } else {
        result = memcmp(a.str, b.str, a.len);
    }
    return result;
}

int so_cmp_c(So a, So b) {
    if(a.len != b.len) return a.len - b.len;
    for(size_t i = 0; i < a.len; ++i) {
        char ca = a.str[i];
        char cb = b.str[i];
        if(tolower((int)ca) != tolower((int)cb)) return ca - cb;
    }
    return 0;
}

int so_cmp_cs(So a, So b) {
    size_t less;
    if(a.len != b.len) less = a.len < b.len ? a.len : b.len;
    else less = a.len;
    for(size_t i = 0; i < less; ++i) {
        char ca = a.str[i];
        char cb = b.str[i];
        if(tolower((int)ca) != tolower((int)cb)) return ca - cb;
    }
    return 0;
}

/* }}} */

/* compare {{{ */
#include <rl/err.h>

int so_cmp_p(So *a, So *b) {
    printff("ptr %p <> %p",a,b);
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmp(*a, *b);
}

int so_cmp_sp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmp_s(*a, *b);
}

int so_cmp_cp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmp_c(*a, *b);
}

int so_cmp_csp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmp_cs(*a, *b);
}

/*}}}*/

/* compare begin {{{ */

int so_cmp0(So a, So b) {
    if(a.len < b.len) return a.len - b.len;
    a.len = b.len;
    return so_cmp(a, b);
}

int so_cmp0_c(So a, So b) {
    if(a.len < b.len) return a.len - b.len;
    a.len = b.len;
    return so_cmp_c(a, b);
}

int so_cmp0_s(So a, So b) {
    if(a.len < b.len) return a.len - b.len;
    a.len = b.len;
    return so_cmp_c(a, b);
}

int so_cmp0_cs(So a, So b) {
    if(a.len < b.len) return a.len - b.len;
    a.len = b.len;
    return so_cmp_cs(a, b);
}

int so_cmp0_p(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmp0(*a, *b);
}

int so_cmp0_sp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmp0_s(*a, *b);
}

int so_cmp0_cp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmp0_c(*a, *b);
}

int so_cmp0_csp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmp0_cs(*a, *b);
}

/*}}}*/

/* compare end {{{ */

int so_cmpE(So a, So b) {
    if(a.len < b.len) return a.len - b.len;
    size_t delta = a.len - b.len;
    so_shift(&a, delta);
    return so_cmp(a, b);
}

int so_cmpE_c(So a, So b) {
    if(a.len < b.len) return a.len - b.len;
    size_t delta = a.len - b.len;
    so_shift(&a, delta);
    return so_cmp_c(a, b);
}

int so_cmpE_s(So a, So b) {
    if(a.len < b.len) return a.len - b.len;
    size_t delta = a.len - b.len;
    so_shift(&a, delta);
    return so_cmp_s(a, b);
}

int so_cmpE_cs(So a, So b) {
    if(a.len < b.len) return a.len - b.len;
    size_t delta = a.len - b.len;
    so_shift(&a, delta);
    return so_cmp_cs(a, b);
}

int so_cmpE_p(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmpE(*a, *b);
}

int so_cmpE_cp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmpE_c(*a, *b);
}

int so_cmpE_sp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmpE_s(*a, *b);
}

int so_cmpE_csp(So *a, So *b) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmpE_cs(*a, *b);
}

/*}}}*/


int so_cmpx(So a, So b, So_Cmp_Attr attr) {
    if((attr & SO_CMP_BEGIN) && (attr & SO_CMP_END)) return -1;
    if(attr & SO_CMP_BEGIN) {
        if( (attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE)) return so_cmp0_cs(a, b);
        if(!(attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE)) return so_cmp0_s(a, b);
        if( (attr & SO_CMP_CASE_INSENSITIVE)) return so_cmp0_c(a, b);
        return so_cmp0(a, b);
    } else if(attr & SO_CMP_END) {
        if( (attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE)) return so_cmpE_cs(a, b);
        if(!(attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE)) return so_cmpE_s(a, b);
        if( (attr & SO_CMP_CASE_INSENSITIVE)) return so_cmpE_c(a, b);
        return so_cmpE(a, b);
    } else {
        if( (attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE)) return so_cmp_cs(a, b);
        if(!(attr & SO_CMP_CASE_INSENSITIVE) &&  (attr & SO_CMP_SORTABLE)) return so_cmp_s(a, b);
        if( (attr & SO_CMP_CASE_INSENSITIVE)) return so_cmp_c(a, b);
    }
    return so_cmp(a, b);
}

int so_cmpx_p(So *a, So *b, So_Cmp_Attr attr) {
    if(!a && !b) return 0;
    if(!a) return so_len(*b);
    if(!b) return so_len(*a);
    return so_cmpx(*a, *b, attr);
}


