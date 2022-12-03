#include <gtest/gtest.h>
#include "CYK.h"

bool check(const std::vector<int>& word) {
  std::unordered_set<Rule*> rules = {new Rule(1, {-1, 1, -2, 1}), new Rule(1, {})};
  CYK cyk;
  auto new_rules = cyk.Create(rules, 1);
  bool answer = cyk.Check(word);
  for (auto& rule : new_rules) {
    delete rule;
  }
  return answer;
}

TEST(testPSP, test1) {
  ASSERT_TRUE(check({-1, -2}));
}

TEST(testPSP, test2) {
  ASSERT_FALSE(check({-2, -1}));
}

TEST(testPSP, test3) {
  ASSERT_TRUE(check({}));
}

TEST(testPSP, test4) {
  ASSERT_TRUE(check({-1, -1, -2, -2}));
}

TEST(testPSP, test5) {
  ASSERT_TRUE(check({-1, -2, -1, -2}));
}

TEST(testPSP, test6) {
  ASSERT_FALSE(check({-1, -2, -2, -1}));
}

TEST(testPSP, test7) {
  ASSERT_FALSE(check({-2, -1, -1, -2}));
}

TEST(testPSP, test8) {
  ASSERT_FALSE(check({-1}));
}

TEST(testPSP, test9) {
  ASSERT_FALSE(check({-2}));
}

TEST(testPSP, test10) {
  ASSERT_FALSE(check({-1, -2, -2}));
}

TEST(testPSP, test11) {
  ASSERT_FALSE(check({-1, -1, -1}));
}

TEST(testPSP, test12) {
  ASSERT_FALSE(check({-527, -93356}));
}

TEST(testPSP, test13) {
  ASSERT_FALSE(check({17, 83}));
}