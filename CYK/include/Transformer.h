#include <queue>
#include <unordered_map>
#include <utility>
#include "Rule.h"
#pragma once

class Transformer {
public:
  explicit Transformer(std::unordered_set<Rule*> rules, int start, int max_letter);
  void Transform();
  std::unordered_set<Rule*> GetRules();
  int GetStart();

protected:
  std::unordered_set<Rule*> rules;
  int start;
  int max_letter;
  void StepOne();
  void StepTwo();
  void StepThree();
  void StepFour();
  void StepFiveAndSix();
  void StepSeven();

  class Dfs {
  public:
    Dfs(int start, std::unordered_set<int>& used,
        std::unordered_map<int, std::unordered_set<int>>& all_bad_to_by_letter);
    void DoDfs(int pos);

  protected:
    std::unordered_set<int>& used;
    std::unordered_map<int, std::unordered_set<int>>& all_bad_to_by_letter;
  };
};
