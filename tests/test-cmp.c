#include "../src/so.h"
#include "../src/so-cmp.h"
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

void randcstr(char *s, size_t len) {
    for(size_t i = 0; i < len; ++i) {
        s[i] = fast_rand() % ('z' - 'A') + 'A';
    }
}

void fill_data(char **tmp, size_t n, size_t len, size_t i0, size_t iE) {
    printf("fill %zu..%zu\n", i0*2, iE*2);
    char tmp2[len];
    for(size_t i = i0*2; i < 2*iE; ++i) {
        //tmp[i] = malloc(len);
        randcstr(tmp2, len);
        tmp[i] = ((char *)tmp) + sizeof(char *) * n*2 + i * len;
        memcpy(tmp[i], tmp2, len);
        //if(!((i + 1) % 10000)) { printf("\r%f%%\r", 100.0*(double)(i+1)/(double)(2*n)); fflush(stdout); }
        //if(!((i + 1) % 100)) { printf("%f%%\n", 100.0*(double)(i+1-2*i0)/(double)(2*iE-2*i0)); } 
        //printf("\r%f%%\n", 100.0*(double)(i+1)/(double)(2*n));
    }
}

void create_data(char ***tmp, int **result, size_t n, size_t len) {
    size_t bytes = sizeof(char *) * n*2 + (n*2*len);
    //size_t bytes = sizeof(char *) * n*2;
    printf("%zu", bytes);
    //fflush(stdout);
    *tmp = malloc(bytes);
    bytes = sizeof(int) * n * 2;
    printf("+%zu ", bytes);
    //fflush(stdout);
    printf("\r");
    *result = malloc(bytes);
}

void run_test_nocopy(char **tmp, int *result, size_t n, size_t len) {
    struct timespec t0, tE, tD;
    clock_gettime(CLOCK_REALTIME, &t0);
    for(size_t i = 0; i < n; ++i) {
        //printf("%zu:%zu[%.*s %.*s]\n", len, so_len(a), SO_F(a), SO_F(b));
        So a = so_ll(tmp[i], len);
        So b = so_ll(tmp[i+n], len);
        result[i] = so_cmp(a, b);
    }
    clock_gettime(CLOCK_REALTIME, &tE);
    tD = diff_timespec(&tE, &t0);
    printf("%s %zu.%09zus ", __func__, tD.tv_sec, tD.tv_nsec);
    printf("%zux%zu", n, len);
    size_t nzero = 0;
    for(size_t i = 0; i < n; ++i) {
        if(!result[i]) ++nzero;
    }
    printf(", nzero %zu\n", nzero);
}

void run_test(char **tmp, int *result, size_t n, size_t len) {
    struct timespec t0, tE, tD;
    So a = {0}, b = {0};
    clock_gettime(CLOCK_REALTIME, &t0);
    for(size_t i = 0; i < n; ++i) {
        //printf("%zu:%zu[%.*s %.*s]\n", len, so_len(a), SO_F(a), SO_F(b));
        so_copy(&a, so_ll(tmp[i], len));
        so_copy(&b, so_ll(tmp[i+n], len));
        so_push(&a, 'x');
        so_push(&b, 'x');
        result[i] = so_cmp(a, b);
        so_clear(&a);
        so_clear(&b);
    }
    clock_gettime(CLOCK_REALTIME, &tE);
    so_free(&a);
    so_free(&b);
    tD = diff_timespec(&tE, &t0);
    printf("%s %zu.%09zus ", __func__, tD.tv_sec, tD.tv_nsec);
    printf("%zux%zu", n, len);
    size_t nzero = 0;
    for(size_t i = 0; i < n; ++i) {
        if(!result[i]) ++nzero;
    }
    printf(", nzero %zu\n", nzero);
}

void run_test_eq(char **tmp, int *result, size_t n, size_t len) {
    struct timespec t0, tE, tD;
    So a = {0}, b = {0};
    clock_gettime(CLOCK_REALTIME, &t0);
    for(size_t i = 0; i < n*2; ++i) {
        so_copy(&a, so_ll(tmp[i], len));
        so_copy(&b, so_ll(tmp[i], len));
        so_push(&a, 'x');
        so_push(&b, 'x');
        result[i] = so_cmp(a, b);
        so_clear(&a);
        so_clear(&b);
    }
    clock_gettime(CLOCK_REALTIME, &tE);
    so_free(&a);
    so_free(&b);
    tD = diff_timespec(&tE, &t0);
    printf("%s %zu.%09zus ", __func__, tD.tv_sec, tD.tv_nsec);
    printf("%zux%zu", n*2, len);
    size_t nzero = 0;
    for(size_t i = 0; i < n*2; ++i) {
        if(!result[i]) ++nzero;
    }
    printf(", nzero %zu\n", nzero);
}

void run_test_eq_nocopy(char **tmp, int *result, size_t n, size_t len) {
    struct timespec t0, tE, tD;
    clock_gettime(CLOCK_REALTIME, &t0);
    for(size_t i = 0; i < n*2; ++i) {
        So a = so_ll(tmp[i], len);
        So b = so_ll(tmp[i], len);
        result[i] = so_cmp(a, b);
    }
    clock_gettime(CLOCK_REALTIME, &tE);
    tD = diff_timespec(&tE, &t0);
    printf("%s %zu.%09zus ", __func__, tD.tv_sec, tD.tv_nsec);
    printf("%zux%zu", n*2, len);
    size_t nzero = 0;
    for(size_t i = 0; i < n*2; ++i) {
        if(!result[i]) ++nzero;
    }
    printf(", nzero %zu\n", nzero);
}

typedef struct FillJob {
    char **tmp;
    size_t n;
    size_t len;
    size_t i0;
    size_t iE;
} FillJob;

void *filljob(void *void_filljob) {
    FillJob *fj = void_filljob;
    fill_data(fj->tmp, fj->n, fj->len, fj->i0, fj->iE);
    return 0;
}

int main(void) {
    size_t nmin = 1000;
    size_t ntimes = 3;
    size_t lentarget = 4096 * 16;

    printf("setting up..\n");
    size_t imax = 0;
    for(size_t i = nmin, n = 0; n < ntimes; i *= 10, ++n) {
        imax = i;
    }
    size_t lenmax = 0;
    for(size_t len = 2; len <= lentarget; len *= 2) {
        lenmax = len;
    }
    char **tmp;
    int *result;
    printf("nmax %zu, lenmax %zu\n", imax, lenmax - 1);
    create_data(&tmp, &result, imax, lenmax - 1);
    FillJob job_data[jobs];
    size_t i0s[jobs];
    size_t iEs[jobs];
    size_t idelta = imax / jobs;
    pthread_t job_th[jobs];
    for(size_t i = 0; i < jobs; ++i) {
        if(i + 1 == jobs && jobs > 1) {
            i0s[i] = iEs[i - 1];
            iEs[i] = imax;
        } else if(i) {
            i0s[i] = iEs[i - 1];
            iEs[i] = i0s[i] + idelta;
        } else {
            i0s[i] = 0;
            iEs[i] = idelta;
        }
        //printf("[%2zu] i0 %zu iE %zu\n", i, i0s[i], iEs[i]);
        job_data[i].tmp = tmp;
        job_data[i].len = lenmax - 1;
        job_data[i].n = imax;
        job_data[i].i0 = i0s[i];
        job_data[i].iE = iEs[i];
        fast_srand(rand());
    }
    printf("filling data..\n");
    for(size_t i = 0; i < jobs; ++i) {
        pthread_create(&job_th[i], 0, filljob, &job_data[i]);
    }
    for(size_t i = 0; i < jobs; ++i) {
        pthread_join(job_th[i], 0);
    }
    printf("filled data.\n");

    for(size_t i = nmin, n = 0; n < ntimes; i *= 10, ++n) {
        for(size_t len = 2; len <= lentarget; len *= 2) {
            run_test(tmp, result, i, len - 1);
        }
    }

    for(size_t i = nmin, n = 0; n < ntimes; i *= 10, ++n) {
        for(size_t len = 2; len <= lentarget; len *= 2) {
            run_test_eq(tmp, result, i, len - 1);
        }
    }

    for(size_t i = nmin, n = 0; n < ntimes; i *= 10, ++n) {
        for(size_t len = 2; len <= lentarget; len *= 2) {
            run_test_nocopy(tmp, result, i, len - 1);
        }
    }

    for(size_t i = nmin, n = 0; n < ntimes; i *= 10, ++n) {
        for(size_t len = 2; len <= lentarget; len *= 2) {
            run_test_eq_nocopy(tmp, result, i, len - 1);
        }
    }

    free(tmp);
    free(result);
    return 0;
}

