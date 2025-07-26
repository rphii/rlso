#include "test.h"

int main(void) {
    So_Uc_Point p = {0};
    So_Uc_Point q = {0};
    So so = so(0);
    /* 0xFFFD ; Replacement Character */
    p.val = 0xFFFD;
    EXPECT(so_uc_fmt_point(&so, &p), 0);
    EXPECT(so_len(so), 3);
    EXPECT((unsigned char)so_at(so, 0), 0xEF);
    EXPECT((unsigned char)so_at(so, 1), 0xBF);
    EXPECT((unsigned char)so_at(so, 2), 0xBD);
    EXPECT(so_uc_point(so, &q), 0);
    EXPECT(q.bytes, p.bytes);
    EXPECT(q.val, p.val);
    so_free(&so);
    return 0;
}

