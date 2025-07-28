#ifndef TEST_H

#include <rl/err.h>
#include "../src/so.h"
#include "../src/so-uc.h"
#include "../src/so-cmp.h"
#include "../src/so-env.h"
#include "../src/so-trim.h"
#include "../src/so-file.h"
#include "../src/so-print.h"
#include "../src/so-split.h"
#include "../src/so-splice.h"

#define EXPECT(expr, val)   \
    ASSERT(expr == val, "expected true")

#define NEXPECT(expr, val)   \
    ASSERT(expr != val, "expected true")

#define TEST_H
#endif

