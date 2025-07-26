#include "test.h"

int main(void) {
    So_Uc_Point p = {0};
    So_Uc_Point q = {0};
    So so = so(0);
    /* 0x7FFFFFFF ; ? */
    p.val = 0x7FFFFFFF;
    EXPECT(so_uc_fmt_point(&so, &p), 0);
    EXPECT(so_len(so), 6);
    EXPECT((unsigned char)so_at(so, 0), 0xFD);
    EXPECT((unsigned char)so_at(so, 1), 0xBF);
    EXPECT((unsigned char)so_at(so, 2), 0xBF);
    EXPECT((unsigned char)so_at(so, 3), 0xBF);
    EXPECT((unsigned char)so_at(so, 4), 0xBF);
    EXPECT((unsigned char)so_at(so, 5), 0xBF);
    EXPECT(so_uc_point(so, &q), 0);
    printff("bytes q %u, p %u", q.bytes, p.bytes);
    EXPECT(q.bytes, p.bytes);
    EXPECT(q.val, p.val);
    so_clear(&so);
    return 0;
}

