#ifndef Q_ASSERT_H
#define Q_ASSERT_H

#include "cg_local.h"

#include <signal.h>

#define FLT_DECIMAL_DIG 9

#define static_assert(x, m) _Static_assert(x, m)

#ifdef NDEBUG
#  define assert(x)
#  define ASSERT_TRUE(x)
#  define ASSERT_FALSE(x)
#  define ASSERT_EQ(x, y)
#  define ASSERT_NE(x, y)
#  define ASSERT_GT(x, y)
#  define ASSERT_LT(x, y)
#  define ASSERT_GE(x, y)
#  define ASSERT_LE(x, y)
#  define ASSERT_FLOAT_EQ(x, y)
#  define ASSERT_FLOAT_GE(x, y)
#else
#  define assert(x)                                                                                                    \
    if (!(x))                                                                                                          \
    {                                                                                                                  \
      printf("(%s:%d) %s -> %.*g\n", __FILE__, __LINE__, #x, FLT_DECIMAL_DIG, (double)(intptr_t)(x));                  \
      raise(SIGABRT);                                                                                                  \
    }
#  define ASSERT_TRUE(x)                                                                                               \
    if (!(x)) trap_Error(vaf("(%s:%d) %s -> %.*g\n", __FILE__, __LINE__, #x, FLT_DECIMAL_DIG, (double)(x)));
#  define ASSERT_FALSE(x)                                                                                              \
    if (!(!(x))) trap_Error(vaf("(%s:%d) !(%s) -> !(%.*g)\n", __FILE__, __LINE__, #x, FLT_DECIMAL_DIG, (double)(x)));
#  define ASSERT_EQ(x, y)                                                                                              \
    if (!((x) == (y)))                                                                                                 \
      trap_Error(vaf(                                                                                                  \
        "(%s:%d) %s == %s -> %.*g == %.*g\n",                                                                          \
        __FILE__,                                                                                                      \
        __LINE__,                                                                                                      \
        #x,                                                                                                            \
        #y,                                                                                                            \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(intptr_t)(x),                                                                                         \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(intptr_t)(y)));
#  define ASSERT_NE(x, y)                                                                                              \
    if (!((x) != (y)))                                                                                                 \
      trap_Error(vaf(                                                                                                  \
        "(%s:%d) %s != %s -> %.*g != %.*g\n",                                                                          \
        __FILE__,                                                                                                      \
        __LINE__,                                                                                                      \
        #x,                                                                                                            \
        #y,                                                                                                            \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(intptr_t)(x),                                                                                         \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(intptr_t)(y)));
#  define ASSERT_GT(x, y)                                                                                              \
    if (!((x) > (y)))                                                                                                  \
      trap_Error(vaf(                                                                                                  \
        "(%s:%d) %s > %s -> %.*g > %.*g\n",                                                                            \
        __FILE__,                                                                                                      \
        __LINE__,                                                                                                      \
        #x,                                                                                                            \
        #y,                                                                                                            \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(x),                                                                                                   \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(y)));
#  define ASSERT_LT(x, y)                                                                                              \
    if (!((x) < (y)))                                                                                                  \
      trap_Error(vaf(                                                                                                  \
        "(%s:%d) %s < %s -> %.*g < %.*g\n",                                                                            \
        __FILE__,                                                                                                      \
        __LINE__,                                                                                                      \
        #x,                                                                                                            \
        #y,                                                                                                            \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(x),                                                                                                   \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(y)));
#  define ASSERT_GE(x, y)                                                                                              \
    if (!((x) >= (y)))                                                                                                 \
      trap_Error(vaf(                                                                                                  \
        "(%s:%d) %s >= %s -> %.*g >= %.*g\n",                                                                          \
        __FILE__,                                                                                                      \
        __LINE__,                                                                                                      \
        #x,                                                                                                            \
        #y,                                                                                                            \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(x),                                                                                                   \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(y)));
#  define ASSERT_LE(x, y)                                                                                              \
    if (!((x) <= (y)))                                                                                                 \
      trap_Error(vaf(                                                                                                  \
        "(%s:%d) %s <= %s -> %.*g <= %.*g\n",                                                                          \
        __FILE__,                                                                                                      \
        __LINE__,                                                                                                      \
        #x,                                                                                                            \
        #y,                                                                                                            \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(x),                                                                                                   \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(y)));
#  define ASSERT_FLOAT_EQ(x, y)                                                                                        \
    if (!(fabsf((x) - (y)) <= fabsf(((x) + (y)) / 2) * 1.e-6f))                                                        \
      trap_Error(vaf(                                                                                                  \
        "(%s:%d) |(%s) - (%s)| <= |((%s) + (%s)) / 2| * 1e-6 -> |%.*g - %.*g| <= |%.*g| * 1e-6\n",                     \
        __FILE__,                                                                                                      \
        __LINE__,                                                                                                      \
        #x,                                                                                                            \
        #y,                                                                                                            \
        #x,                                                                                                            \
        #y,                                                                                                            \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(x),                                                                                                   \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(y),                                                                                                   \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(((x) + (y)) / 2)));
#  define ASSERT_FLOAT_GE(x, y)                                                                                        \
    if (!((x) - (y) >= fabsf(((x) + (y)) / 2) * -1.e-6f))                                                              \
      trap_Error(vaf(                                                                                                  \
        "(%s:%d) (%s - %s) >= |((%s) + (%s)) / 2| * -1e-6 -> %.*g - %.*g >= |%.*g| * -1e-6\n",                         \
        __FILE__,                                                                                                      \
        __LINE__,                                                                                                      \
        #x,                                                                                                            \
        #y,                                                                                                            \
        #x,                                                                                                            \
        #y,                                                                                                            \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(x),                                                                                                   \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(y),                                                                                                   \
        FLT_DECIMAL_DIG,                                                                                               \
        (double)(((x) + (y)) / 2)));
#endif

#endif // Q_ASSERT_H
