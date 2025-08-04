#ifndef TEST_H

#include <rl/err.h>
#include <rl/array.h>
#include <rl/platform-detect.h>
#include "../src/so.h"
#include "../src/so-as.h"
#include "../src/so-fx.h"
#include "../src/so-uc.h"
#include "../src/so-cmp.h"
#include "../src/so-cmp-attr.h"
#include "../src/so-env.h"
#include "../src/so-trim.h"
#include "../src/so-find.h"
#include "../src/so-file.h"
#include "../src/so-path.h"
#include "../src/so-count.h"
#include "../src/so-input.h"
#include "../src/so-print.h"
#include "../src/so-split.h"
#include "../src/so-splice.h"
#include "../src/so-print.h"
#include "../src/vso.h"

#define EXPECT(expr, val)   do {\
    size_t a = ((expr)); \
    printf("==%zu <- %s " F("*", FG_BL_B) " " F("%s:%u", FG_BK_B) "\n=>%zu\n", (size_t)a, ERR_STRINGIFY(expr), __func__, __LINE__, (size_t)(val)); \
    ASSERT(a == val, "expected true"); } while(0)

#define EXPECT_CMP(a, b)   do {\
    printf("==%.*s\n=>%.*s\n", SO_F((a)), SO_F((b))); \
    EXPECT(so_cmp(a, b), 0); } while(0)

#define NEXPECT(expr, val)   \
    ASSERT(expr != val, "expected true")

#define TEST_H
#endif

