#include "../src/so.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>

#define jobs 16

struct timespec diff_timespec(const struct timespec *time1,
    const struct timespec *time0) {
  assert(time1);
  assert(time0);
  struct timespec diff = {.tv_sec = time1->tv_sec - time0->tv_sec, //
      .tv_nsec = time1->tv_nsec - time0->tv_nsec};
  if (diff.tv_nsec < 0) {
    diff.tv_nsec += 1000000000; // nsec/sec
    diff.tv_sec--;
  }
  return diff;
}
double t_timespec(const struct timespec time) {
    return time.tv_sec + (double)time.tv_nsec / 1e9;
}

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

void run_test_rand(size_t n, size_t len) {
    struct timespec t0, tE, tD;
    So a = {0}, b = {0};
    clock_gettime(CLOCK_REALTIME, &t0);
    for(size_t i = 0; i < n; ++i) {
        so_clear(&a);
        for(size_t j = 0; j < len; ++j) {
            so_push(&a, fast_rand());
        }
    }
    clock_gettime(CLOCK_REALTIME, &tE);
    so_free(&a);
    so_free(&b);
    tD = diff_timespec(&tE, &t0);
    printf("%s %zu.%09zus ", __func__, tD.tv_sec, tD.tv_nsec);
    printf("%zux%zu", n, len);
    double c = n * len;
    double t = t_timespec(tD);
    printf(" %.3f ns/push (%.2f Mbyte/sec)\n", 1e9*t/c, c/t/1e6);
}

void run_test(size_t n, size_t len) {
    struct timespec t0, tE, tD;
    So a = {0}, b = {0};
    clock_gettime(CLOCK_REALTIME, &t0);
    for(size_t i = 0; i < n; ++i) {
        so_clear(&a);
        for(size_t j = 0; j < len; ++j) {
            so_push(&a, fast_rand());
        }
    }
    clock_gettime(CLOCK_REALTIME, &tE);
    so_free(&a);
    so_free(&b);
    tD = diff_timespec(&tE, &t0);
    printf("%s %zu.%09zus ", __func__, tD.tv_sec, tD.tv_nsec);
    printf("%zux%zu", n, len);
    double c = n * len;
    double t = t_timespec(tD);
    printf(" %.3f ns/push (%.2f Mbyte/sec)\n", 1e9*t/c, c/t/1e6);
}

void run_test_ext(size_t n, size_t len) {
    struct timespec t0, tE, tD;
    So a = {0}, b = {0};
    for(size_t i = 0; i < len; ++i) so_push(&b, fast_rand());
    clock_gettime(CLOCK_REALTIME, &t0);
    for(size_t i = 0; i < n; ++i) {
        so_clear(&a);
        for(size_t j = 0; j < len; ++j) {
            so_extend(&a, b);
        }
    }
    clock_gettime(CLOCK_REALTIME, &tE);
    so_free(&a);
    so_free(&b);
    tD = diff_timespec(&tE, &t0);
    printf("%s %zu.%09zus ", __func__, tD.tv_sec, tD.tv_nsec);
    printf("%zux%zu", n, len);
    double c = n * len;
    double t = t_timespec(tD);
    printf(" %.3f ns/push (%.2f Mbyte/sec)\n", 1e9*t/c, c/t/1e6);
}


int main(void) {
    srand(0);
    size_t nmin = 10000;
    size_t ntimes = 3;
    size_t lentarget = 4096 * 1;

    for(size_t i = nmin, n = 0; n < ntimes; i *= 10, ++n) {
        for(size_t len = 2; len <= lentarget; len *= 2) {
            run_test(i, len - 1);
        }
    }

    for(size_t i = nmin, n = 0; n < ntimes; i *= 10, ++n) {
        for(size_t len = 2; len <= lentarget; len *= 2) {
            run_test_rand(i, len - 1);
        }
    }

    for(size_t i = nmin, n = 0; n < ntimes; i *= 10, ++n) {
        for(size_t len = 2; len <= lentarget; len *= 2) {
            run_test_ext(i, len - 1);
        }
    }

    return 0;
}


