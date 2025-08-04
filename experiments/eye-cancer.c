#include "../src/so.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

static unsigned int g_seed;

// Used to seed the generator.           
void fast_srand(int seed);
inline void fast_srand(int seed) {
    g_seed = seed;
}

// Compute a pseudorandom integer.
// Output value in range [0, 32767]
int fast_rand(void);
inline int fast_rand(void) {
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

int main(void) {
    
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("lines %d\n", w.ws_row);
    printf("columns %d\n", w.ws_col);
    printf("Warning! This program causes eye-cancer (epilleptic warning!). Proceed? Type 'yes': ");
    So user = SO;
    So buf = SO;
    So_Align al = { .iE = w.ws_col };
    So_Fx fx = { .align = &al };
    so_input(&user);
    if(so_cmp(user, so("yes"))) goto exit;

    while(true) {
        so_clear(&buf);
        so_al_rewind(&al);
        for(size_t i = 1; i < w.ws_col * w.ws_row; ++i) {
            fx.fg.r = fast_rand();
            fx.fg.g = fast_rand();
            fx.fg.b = fast_rand();
            fx.bg.r = fast_rand();
            fx.bg.g = fast_rand();
            fx.bg.b = fast_rand();
            fx.bold = fast_rand() % 2;
            fx.italic = fast_rand() % 2;
            fx.underline = fast_rand() % 2;
            char c = fast_rand() % ('z'-'A')+'A';
            so_fmt_fx(&buf, fx, "%c", c);
        }
        gotoxy(1,1);
        so_print(buf);
        fflush(stdout);
    }

exit:
    so_al_free(&al);
    so_free(&user);
    so_free(&buf);
    return 0;
}

