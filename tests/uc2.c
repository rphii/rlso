#include "test.h"

int main(void) {
    So_Uc_Point p = {0};
    So_Uc_Point q = {0};
    So so = so(0);
    /* 0x07FF ; Nko Taman Sign */
    p.val = 0x7FF;
    EXPECT(so_uc_fmt_point(&so, &p), 0);
    EXPECT(so_len(so), 2);
    EXPECT((unsigned char)so_at(so, 0), 0xDF);
    EXPECT((unsigned char)so_at(so, 1), 0xBF);
    EXPECT(so_uc_point(so, &q), 0);
    EXPECT(q.bytes, p.bytes);
    EXPECT(q.val, p.val);
    so_clear(&so);
    return 0;
}

