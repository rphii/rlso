#include "test.h"

int main(void) {
    So_Uc_Point p = {0};
    So_Uc_Point q = {0};
    So so = so(0);
    /* 123 */
    p.val = 123;
    EXPECT(so_uc_fmt_point(&so, &p), 0);
    EXPECT(so_len(so), 1);
    EXPECT(so_at(so, 0), 123);
    EXPECT(so_uc_point(so, &q), 0);
    EXPECT(q.bytes, p.bytes);
    EXPECT(q.val, p.val);
    so_clear(&so);
    return 0;
}

