#include "Transformer.h"
#include <set>
#pragma once

class CYK {
public:
  CYK();
  std::unordered_set<Rule*> Create(const std::unordered_set<Rule*>& new_rules, int new_start);
  bool Check(const std::vector<int>& word);

protected:
  int start;
  bool is_epsilon = false;
  std::unordered_map<int, std::set<std::pair<int, int>>> middle_rules;
  std::unordered_map<int, std::unordered_set<int>> end_rules;
};

