#ifndef TEST_H

#include <rl/err.h>
#include "../src/so.h"
#include "../src/so-uc.h"
#include "../src/so-print.h"

#define EXPECT(expr, val)   \
    ASSERT(expr == val, "expected true")

#define NEXPECT(expr, val)   \
    ASSERT(expr != val, "expected true")

#define TEST_H
#endif

