#include "func_for_tests.h"

TEST(sample_tests, test1) {
    ASSERT_TRUE(makeTest("ab+c.aba.*.bac.+.+* a 4", false));
}

TEST(sample_tests, test2) {
    ASSERT_TRUE(makeTest("acb..bab.c.*.ab.ba.+.+*a. b 2", true));
}