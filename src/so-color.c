#include "so-color.h"
#include "so-core.h"
#include "so-print.h"
#include "so-as.h"
#include "so-cmp.h"
#include "so-trim.h"
#include "so-split.h"
#include "so-splice.h"
#include "so-count.h"
#include "so-fx.h"
#include "so-find.h"

ErrDecl so_as_color(So so, Color *out) {
    Color result = COLOR_NONE;
    if(!so_len(so)) return -1;
    if(so_at0(so) == '#') {
        so_shift(&so, 1);
        if(so_len(so) >= 2) {
            if(so_as_u8(so_iE(so, 2), &result.r, 16)) return -1;
            so_shift(&so, 2);
        }
        if(so_len(so) >= 2) {
            if(so_as_u8(so_iE(so, 2), &result.g, 16)) return -1;
            so_shift(&so, 2);
        }
        if(so_len(so) >= 2) {
            if(so_as_u8(so_iE(so, 2), &result.b, 16)) return -1;
            so_shift(&so, 2);
        }
        if(so_len(so) >= 2) {
            if(so_as_u8(so_iE(so, 2), &result.a, 16)) return -1;
            so_shift(&so, 2);
        }
        if(so_len(so)) return -1;
    } else {
        int n_channels = 0;
        int ch[4] = { -1, -1, -1, -1 };
        for(int i = 0; i < 4; ++i) {
            if (ch[0] < 0 && !so_cmp0_c(so, so("r"))) {
                ch[0] = i;
                n_channels += so_shift(&so, 1);
            } else
            if (ch[1] < 0 && !so_cmp0_c(so, so("g"))) {
                ch[1] = i;
                n_channels += so_shift(&so, 1);
            } else
            if (ch[2] < 0 && !so_cmp0_c(so, so("b"))) {
                ch[2] = i;
                n_channels += so_shift(&so, 1);
            } else
            if (ch[3] < 0 && !so_cmp0_c(so, so("a"))) {
                ch[3] = i;
                n_channels += so_shift(&so, 1);
            } else
            if (ch[0] < 0 && ch[1] < 0 && ch[2] < 0 && 
                    !so_cmp0_c(so, so("w"))) {
                ch[0] = i;
                ch[1] = i;
                ch[2] = i;
                n_channels += so_shift(&so, 1);
            }
        }
        size_t nws = so_find_nws(so);
        so_shift(&so, nws);
        if(!so_len(so)) return -1;
        if(so_at0(so) != '(') return -1;
        so_shift(&so, 1);
        So decimals = so_split_ch(so, ')', 0);
        if(so_len(decimals) + 1 != so_len(so)) return -1;
        decimals = so_trim(decimals);
        size_t count_c = so_count_ch(decimals, ',');
        if(count_c + 1 == n_channels) {
            int channel = 0;
            for(So splice = SO; so_splice(decimals, &splice, ','); ++channel) {
                if(so_is_zero(splice)) continue;
                uint8_t val = 0;
                if(so_as_u8(so_trim(splice), &val, 0)) return -1;
                if(ch[0] == channel) result.r = val;
                if(ch[1] == channel) result.g = val;
                if(ch[2] == channel) result.b = val;
                if(ch[3] == channel) result.a = val;
            }
        } else if(!count_c && so_len(decimals) == 2 * n_channels) {
            for(int channel = 0; channel < n_channels; ++channel) {
                uint8_t val = 0;
                if(so_as_u8(so_iE(so, 2), &val, 16)) return -1;
                if(ch[0] == channel) result.r = val;
                if(ch[1] == channel) result.g = val;
                if(ch[2] == channel) result.b = val;
                if(ch[3] == channel) result.a = val;
                so_shift(&so, 2);
            }
        } else {
            return -1;
        }
    }
    *out = result;
    return 0;
}

void so_fmt_color(So *so, Color in, So_Color_Attr attr) {
    So_Fx fx = {0};
    int n_channels = 0;
    Color use = COLOR_NONE;
    if(attr & SO_COLOR_R) { use.r = in.r; }
    if(attr & SO_COLOR_G) { use.g = in.g; }
    if(attr & SO_COLOR_B) { use.b = in.b; }
    if(attr & SO_COLOR_A) { use.a = in.a; } else { use.a = 0xFF; }
    fx.bg = use;
    uint8_t bright = color_as_brightness(use, COLOR_GAMMA_DEFAULT);
    if(bright > 50) {
        fx.fg = COLOR_BLACK;
    } else {
        fx.fg = COLOR_WHITE;
    }
    if(attr & SO_COLOR_HEX) {
        so_fmt_fx(so, fx, "#");
        if(attr & SO_COLOR_R) so_fmt_fx(so, fx, "%02x", in.r);
        if(attr & SO_COLOR_G) so_fmt_fx(so, fx, "%02x", in.g);
        if(attr & SO_COLOR_B) so_fmt_fx(so, fx, "%02x", in.b);
        if(attr & SO_COLOR_A) so_fmt_fx(so, fx, "%02x", in.a);
    } else if(attr & SO_COLOR_DEC) {
        if(attr & SO_COLOR_R) so_fmt_fx(so, fx, "r");
        if(attr & SO_COLOR_G) so_fmt_fx(so, fx, "g");
        if(attr & SO_COLOR_B) so_fmt_fx(so, fx, "b");
        if(attr & SO_COLOR_A) so_fmt_fx(so, fx, "a");
        so_fmt_fx(so, fx, "(");
        int n = 0;
        if(attr & SO_COLOR_R) so_fmt_fx(so, fx, "%s%u", n++ ? ", " : "", in.r);
        if(attr & SO_COLOR_G) so_fmt_fx(so, fx, "%s%u", n++ ? ", " : "", in.g);
        if(attr & SO_COLOR_B) so_fmt_fx(so, fx, "%s%u", n++ ? ", " : "", in.b);
        if(attr & SO_COLOR_A) so_fmt_fx(so, fx, "%s%u", n++ ? ", " : "", in.a);
        so_fmt_fx(so, fx, ")");
    }
}

