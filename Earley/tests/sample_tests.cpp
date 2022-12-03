#include <gtest/gtest.h>
#include "Earley.h"

bool check(const std::vector<int>& word,
           std::unordered_set<Rule*> rules = {new Rule(1, {-1, 1, -2, 1}), new Rule(1, {})}) {
  Earley earley;
  earley.Create(rules, 1);
  bool answer = earley.Check(word);
  for (auto& rule : rules) {
    delete rule;
  }
  return answer;
}

TEST(testPSP, test1) {
  Configuration config0;
  Configuration config2(config0.from, config0.to, config0.value, config0.index);
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

TEST(testPSP, test14) {
  ASSERT_TRUE(check({-1, -2}, {new Rule(1, {1, -1, 1, -2}), new Rule(1, {})}));
}