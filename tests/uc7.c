#include "test.h"

int main(void) {
    So_Uc_Point p = {0};
    So_Uc_Point q = {0};
    So so = so(0);
    /* 0x80000000 ; error */
    p.val = 0x80000000;
    NEXPECT(so_uc_fmt_point(&so, &p), 0);
    EXPECT(so_len(so), 0);
    EXPECT(p.bytes, 0);
    so_push(&so, 0xFF);
    NEXPECT(so_uc_point(so, &q), 0);
    EXPECT(q.bytes, p.bytes);
    so_clear(&so);
    so_push(&so, 0xC0);
    so_push(&so, 0xF0);
    NEXPECT(so_uc_point(so, &q), 0);
    so_clear(&so);
    so_push(&so, 0xC0);
    NEXPECT(so_uc_point(so, &q), 0);
    so_push(&so, 0x00);
    NEXPECT(so_uc_point(so, &q), 0);
    so_free(&so);
    return 0;
}


