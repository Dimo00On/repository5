#include <gtest/gtest.h>
#include "CYK.h"

bool check(const std::vector<int>& word, const std::unordered_set<Rule*>& rules) {
  CYK cyk;
  auto new_rules = cyk.Create(rules, 1);
  bool answer = cyk.Check(word);
  for (auto& rule : new_rules) {
    delete rule;
  }
  return answer;
}

TEST(test_bad_rules, test1) {
  ASSERT_TRUE(check({}, {new Rule(1, {2}), new Rule(2, {3, 3}),
                        new Rule(3, {1}), new Rule(1, {1}), new Rule(1, {}), new Rule(5, {-1})}));
}

TEST(test_bad_rules, test2) {
  ASSERT_TRUE(check({}, {new Rule(1, {1}), new Rule(1, {2, 3}), new Rule(2, {-1}), new Rule(3, {-1}),
                         new Rule(1, {2}), new Rule(1, {3}), new Rule(2, {}), new Rule(3, {})}));
}