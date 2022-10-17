#include "func_for_tests.h"

TEST(error_tests, test1) {
    ASSERT_TRUE(makeErrorTest("42 a 4") == 1);
}

TEST(error_tests, test2) {
    ASSERT_TRUE(makeErrorTest("*a a 4") == 2);
}

TEST(error_tests, test3) {
    ASSERT_TRUE(makeErrorTest("+aa a 4") == 2);
}

TEST(error_tests, test4) {
    ASSERT_TRUE(makeErrorTest("aaaa a 4") == 2);
}

TEST(error_tests, test5) {
    ASSERT_TRUE(makeErrorTest("a* a -4") == 3);
}