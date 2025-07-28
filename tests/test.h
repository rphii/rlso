#ifndef TEST_H

#include <rl/err.h>
#include <rl/platform-detect.h>
#include "../src/so.h"
#include "../src/so-uc.h"
#include "../src/so-cmp.h"
#include "../src/so-env.h"
#include "../src/so-trim.h"
#include "../src/so-file.h"
#include "../src/so-path.h"
#include "../src/so-print.h"
#include "../src/so-split.h"
#include "../src/so-splice.h"

#define EXPECT(expr, val)   \
    ASSERT(expr == val, "expected true")

#define EXPECT_CMP(a, b)   do {\
    printf("==%.*s\n:=%.*s\n", SO_F((a)), SO_F((b))); \
    EXPECT(so_cmp(a, b), 0); } while(0)

#define NEXPECT(expr, val)   \
    ASSERT(expr != val, "expected true")

#define TEST_H
#endif

