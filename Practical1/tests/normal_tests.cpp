#include "func_for_tests.h"

TEST(normal_test, test1) {
    ASSERT_TRUE(makeTest("a* z 0", true));
}

TEST(normal_test, test2) {
    ASSERT_TRUE(makeTest("a* z 3", false));
}

TEST(normal_test, test3) {
    ASSERT_TRUE(makeTest("bb.* b 137", true));
}

TEST(normal_test, test4) {
    ASSERT_TRUE(makeTest("a1+ b 0", true));
}

TEST(normal_test, test5) {
    ASSERT_TRUE(makeTest("a1+ b 1", false));
}

TEST(normal_test, test6) {
    ASSERT_TRUE(makeTest("a* b 0", true));
}

TEST(normal_test, test7) {
    ASSERT_TRUE(makeTest("a* b 1", false));
}