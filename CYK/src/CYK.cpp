#include "CYK.h"

CYK::CYK() = default;

std::unordered_set<Rule*> CYK::Create(const std::unordered_set<Rule*>& new_rules, int new_start) {
    int max_letter = 0;
    for (auto& rule : new_rules) {
      max_letter = std::max(max_letter, rule->from);
      for (auto& letter : rule->to) {
        max_letter = std::max(max_letter, letter);
      }
    }
    Transformer transformer(new_rules, new_start, max_letter);
    transformer.Transform();
    std::unordered_set<Rule*> rules = transformer.GetRules();
    start = transformer.GetStart();
    for (auto& rule : rules) {
      if (rule->to.empty() && rule->from == start) {
        is_epsilon = true;
      }
      if (rule->to.size() == 1) {
        end_rules[rule->from].insert(rule->to[0]);
      }
      if (rule->to.size() == 2) {
        middle_rules[rule->from].insert(std::make_pair(rule->to[0], rule->to[1]));
      }
    }
    return rules;
};

bool CYK::Check(const std::vector<int>& word) {
  if (word.empty()) {
    return is_epsilon;
  }
  int size = static_cast<int>(word.size());
  std::vector<std::vector<std::unordered_map<int, bool>>>
      dp(size,std::vector<std::unordered_map<int, bool>>(size));
  for (int i = 0; i < size; ++i) {
    for (auto& rule_pack : end_rules) {
      if (rule_pack.second.count(word[i])) {
        dp[i][i][rule_pack.first] = true;
      }
    }
  }
  for (int length = 2; length <= size; ++length) {
    for (int begin = 0; begin <= size - length; ++begin) {
      int end = begin + length - 1;
      for (auto& rule_pack : middle_rules) {
        for (auto& right_part : rule_pack.second) {
          for (int middle = begin; middle < end; ++middle) {
            dp[begin][end][rule_pack.first] |= (dp[begin][middle][right_part.first] &
                dp[middle + 1][end][right_part.second]);
          }
        }
      }
    }
  }
  return dp[0][size - 1][start];
}