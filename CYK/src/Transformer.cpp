#include "Transformer.h"
#include <set>

Transformer::Transformer(std::unordered_set<Rule*> rules, int start, int max_letter) :
  rules(std::move(rules)), start(start), max_letter(max_letter) {}

void Transformer::Transform() {
  StepOne();
  StepTwo();
  StepThree();
  StepFour();
  StepFiveAndSix();
  StepOne();
  StepTwo();
  StepSeven();
}

std::unordered_set<Rule*> Transformer::GetRules() {
  return rules;
}

int Transformer::GetStart() {
  return start;
}

void Transformer::StepOne() {
  std::unordered_map<int, std::unordered_set<Rule*>> non_generating_letter;
  std::unordered_map<int, std::vector<Rule*>> rules_with_letter;
  for (auto& rule : rules) {
    rule->value = 0;
    std::unordered_set<int> used;
    for (auto& letter : rule->to) {
      if (letter > 0 && !used.count(letter)) {
        ++rule->value;
        used.insert(letter);
        rules_with_letter[letter].push_back(rule);
      }
    }
    non_generating_letter[rule->from].insert(rule);
  }
  bool changed = true;
  std::unordered_set<int> used;
  while (changed) {
    changed = false;
    for (auto& rule_pack : non_generating_letter) {
      for (auto& rule : rule_pack.second) {
        if (rule->value == 0) {
          changed = true;
          if (!used.count(rule_pack.first)) {
            used.insert(rule_pack.first);
            for (auto &other_rule: rules_with_letter[rule_pack.first]) {
              --other_rule->value;
            }
          }
          non_generating_letter[rule_pack.first].erase(rule);
          break;
        }
      }
      if (changed) {
        break;
      }
    }
  }
  for (auto& rule_pack : non_generating_letter) {
    for (auto& rule : rule_pack.second) {
      rules.erase(rule);
      delete rule;
    }
  }
}
void Transformer::StepTwo() {
  std::unordered_map<int, std::vector<Rule*>> rules_by_letter;
  std::unordered_set<int> unreachable;
  for (auto& rule : rules) {
    rule->value = 0;
    rules_by_letter[rule->from].push_back(rule);
    unreachable.insert(rule->from);
  }
  std::queue<int> handle;
  unreachable.erase(start);
  handle.push(start);
  while (!handle.empty()) {
    int next = handle.front();
    handle.pop();
    for (auto& rule : rules_by_letter[next]) {
      for (auto& to : rule->to) {
        if (to > 0 && unreachable.count(to)) {
          unreachable.erase(to);
          handle.push(to);
        }
      }
    }
  }
  for (int letter : unreachable) {
    for (auto& rule : rules_by_letter[letter]) {
      rules.erase(rule);
      delete rule;
    }
  }
}
void Transformer::StepThree() {
  int max_number = max_letter;
  std::unordered_set<int> new_letters;
  for (auto& rule : rules) {
    if (rule->to.size() > 1) {
      for (auto& letter : rule->to) {
        if (letter < 0) {
          if (!new_letters.count(max_letter - letter)) {
            new_letters.insert(max_letter - letter);
          }
          letter = max_letter - letter;
          if (letter > max_number) {
            max_number = letter;
          }
        }
      }
    }
  }
  for (auto& letter : new_letters) {
    auto rule = new Rule(letter, {max_letter - letter});
    rules.insert(rule);
  }
  max_letter = max_number;
}
void Transformer::StepFour() {
  std::unordered_set<Rule*> new_rules;
  std::unordered_set<Rule*> to_delete;
  for (auto& rule : rules) {
    int size = static_cast<int>(rule->to.size());
    if (size > 2) {
      auto new_rule = new Rule(rule->from, {rule->to[0], max_letter + 1});
      new_rules.insert(new_rule);
      ++max_letter;
      for (int i = 1; i < size - 2; ++i) {
        new_rule = new Rule(max_letter, {rule->to[i], max_letter + 1});
        new_rules.insert(new_rule);
        ++max_letter;
      }
      new_rule = new Rule(max_letter, {rule->to[size - 2], rule->to[size - 1]});
      new_rules.insert(new_rule);
      ++max_letter;
      to_delete.insert(rule);
    }
  }
  for (auto& rule : to_delete) {
    rules.erase(rule);
    delete rule;
  }
  for (auto& rule : new_rules) {
    rules.insert(rule);
  }
}
void Transformer::StepFiveAndSix() {
  std::unordered_map<int, std::vector<Rule*>> rules_with_letter;
  std::unordered_set<int> used;
  bool is_start_epsilon_gen = false;
  std::set<Rule> all_rules;
  std::queue<int> new_epsilon;
  {
    std::vector<Rule *> to_delete;
    for (auto &rule: rules) {
      if (rule->to.empty()) {
        used.insert(rule->from);
        new_epsilon.push(rule->from);
        to_delete.push_back(rule);
      }
    }
    for (auto &rule: to_delete) {
      rules.erase(rule);
      delete rule;
    }
  }
  for (auto& rule : rules) {
    all_rules.insert(*rule);
    rule->value = static_cast<int>(rule->to.size());
    for (auto& letter : rule->to) {
      if (letter > 0) {
        rules_with_letter[letter].push_back(rule);
      }
    }
  }
  while (!new_epsilon.empty()) {
    int letter = new_epsilon.front();
    new_epsilon.pop();
    if (letter == start) {
      is_start_epsilon_gen = true;
    }
    for (auto& rule : rules_with_letter[letter]) {
      --rule->value;
      if (rule->to.size() == 2) {
        auto new_rule = new Rule(rule->from, {(rule->to[0] == letter ? rule->to[1] : rule->to[0])});
        if (all_rules.count(*new_rule)) {
          delete new_rule;
        } else {
          rules.insert(new_rule);
          all_rules.insert(*new_rule);
        }
      }
      if (rule->value == 0 && !used.count(rule->from)) {
        new_epsilon.push(rule->from);
        used.insert(rule->from);
      }
    }
  }
  auto new_rule = new Rule(max_letter + 1, {start});
  rules.insert(new_rule);
  start = max_letter + 1;
  if (is_start_epsilon_gen) {
    new_rule = new Rule(max_letter + 1, {});
    rules.insert(new_rule);
  }
  ++max_letter;
}
void Transformer::StepSeven() {
  std::unordered_map<int, std::vector<Rule*>> good_rules_by_letter;
  std::unordered_map<int, std::unordered_set<int>> all_bad_to_by_letter;
  std::unordered_set<int> all_letters;
  std::set<Rule> all_rules;
  {
    std::unordered_set<Rule *> to_delete;
    for (auto &rule: rules) {
      all_letters.insert(rule->from);
      if (rule->to.size() == 1 && rule->to[0] > 0) {
        all_bad_to_by_letter[rule->from].insert(rule->to[0]);
        to_delete.insert(rule);
        continue;
      }
      all_rules.insert(*rule);
      good_rules_by_letter[rule->from].push_back(rule);
    }
    for (auto &rule: to_delete) {
      rules.erase(rule);
      delete rule;
    }
  }
  for (auto& from : all_letters) {
    std::unordered_set<int> used;
    if (!used.count(from)) {
      Dfs(from, used, all_bad_to_by_letter);
    }
    for (auto& letter : all_bad_to_by_letter[from]) {
      if (letter == from) {
        continue;
      }
      for (auto& rule : good_rules_by_letter[letter]) {
        auto new_rule = new Rule(from, rule->to);
        if (all_rules.count(*new_rule)) {
          delete new_rule;
        } else {
          all_rules.insert(*new_rule);
          rules.insert(new_rule);
        }
      }
    }
  }
}

Transformer::Dfs::Dfs(int start, std::unordered_set<int>& used,
                      std::unordered_map<int, std::unordered_set<int>>& all_bad_to_by_letter) :
                      used(used), all_bad_to_by_letter(all_bad_to_by_letter) {
  DoDfs(start);
}

void Transformer::Dfs::DoDfs(int pos) {
  used.insert(pos);
  std::unordered_set<int> add;
  for (auto& to : all_bad_to_by_letter[pos]) {
    if (!used.count(to)) {
      DoDfs(to);
    }
    for (auto &letter: all_bad_to_by_letter[to]) {
      add.insert(letter);
    }
  }
  for (auto& letter : add) {
    all_bad_to_by_letter[pos].insert(letter);
  }
}