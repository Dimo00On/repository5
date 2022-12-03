#include "Earley.h"

Earley::Earley() = default;

void Earley::Create(std::unordered_set<Rule*>& new_rules, int new_start) {
  start = new_start;
  new_rules.insert(new Rule(0, {start}, 0));
  for (auto& rule : new_rules) {
    rules[rule->from].push_back(*rule);
  }
}

bool Earley::Check(const std::vector<int>& new_word) {
  word = new_word;
  length = static_cast<int>(word.size()) + 1;
  end_config_packs.clear();
  middle_config_packs.clear();
  end_config_packs.resize(length, std::vector<std::set<Rule>>(length));
  middle_config_packs.resize(length, std::vector<std::set<Rule>>(length));
  middle_config_packs[0][0].insert(rules[0][0]);
  bool changing = true;
  std::set<Configuration> new_configs;
  while (changing) {
    changing = false;
    changing |= Predict(0, new_configs);
    changing |= Complete(0, new_configs);
  }
  for (int i = 1; i < length; ++i) {
    Scan(i - 1, new_configs);
    changing = true;
    while (changing) {
      changing = false;
      changing |= Predict(i, new_configs);
      changing |= Complete(i, new_configs);
    }
  }
  auto it = end_config_packs[length - 1][0].find(Rule(0, {start}, 1));
  if (it == end_config_packs[length - 1][0].end()) {
    return false;
  }
  return true;
}

void Earley::Scan(int step, std::set<Configuration>& new_configs) {
  for (int i = 0; i < length; ++i) {
    for (auto& config : middle_config_packs[step][i]) {
      if (config.to[config.value] == word[step]) {
        Rule new_config(config.from, config.to, config.value + 1);
        if (config.value + 1 < static_cast<int>(config.to.size())) {
          middle_config_packs[step + 1][i].insert(new_config);
        } else {
          auto it = end_config_packs[step + 1][i].find(new_config);
          if (it == end_config_packs[step + 1][i].end()) {
            end_config_packs[step + 1][i].insert(new_config);
            new_configs.insert(Configuration(new_config, i));
          }
        }
      }
    }
  }
}

bool Earley::Predict(int step, std::set<Configuration>& new_configs) {
  bool answer = false;
  for (int i = 0; i < length; ++i) {
    for (auto& config : middle_config_packs[step][i]) {
      if (config.to[config.value] > 0) {
        for (auto &rule: rules[config.to[config.value]]) {
          Rule new_rule(rule.from, rule.to, 0);
          if (!rule.to.empty()) {
            auto it = middle_config_packs[step][step].find(new_rule);
            if (it == middle_config_packs[step][step].end()) {
              middle_config_packs[step][step].insert(new_rule);
              answer = true;
            }
          } else {
            auto it = end_config_packs[step][step].find(new_rule);
            if (it == end_config_packs[step][step].end()) {
              end_config_packs[step][step].insert(new_rule);
              new_configs.insert(Configuration(rule, step));
              answer = true;
            }
          }
        }
      }
    }
  }
  return answer;
}

bool Earley::Complete(int step, std::set<Configuration>& last_new_configs) {
  bool answer = false;
  std::set<Configuration> new_new_configs;
  for (auto& end_config : end_config_packs[step][step]) {
    for (int i = 0; i < length; ++i) {
      for (auto& config: middle_config_packs[step][i]) {
        if (config.to[config.value] == end_config.from) {
          Rule new_config(config.from, config.to, config.value + 1);
          if (config.value + 1 < static_cast<int>(config.to.size())) {
            auto it = middle_config_packs[step][i].find(new_config);
            if (it == middle_config_packs[step][i].end()) {
              middle_config_packs[step][i].insert(new_config);
              answer = true;
            }
          } else {
            auto it = end_config_packs[step][i].find(new_config);
            if (it == end_config_packs[step][i].end()) {
              end_config_packs[step][i].insert(new_config);
              new_new_configs.insert(Configuration(new_config, i));
              answer = true;
            }
          }
        }
      }
    }
  }
  for (auto& end_config : last_new_configs) {
    for (int i = 0; i < length; ++i) {
      for (auto& config : middle_config_packs[end_config.index][i]) {
        if (config.to[config.value] == end_config.from) {
          Rule new_config(config.from, config.to, config.value + 1);
          if (config.value + 1 < static_cast<int>(config.to.size())) {
            auto it = middle_config_packs[step][i].find(new_config);
            if (it == middle_config_packs[step][i].end()) {
              middle_config_packs[step][i].insert(new_config);
              answer = true;
            }
          } else {
            auto it = end_config_packs[step][i].find(new_config);
            if (it == end_config_packs[step][i].end()) {
              end_config_packs[step][i].insert(new_config);
              new_new_configs.insert(Configuration(new_config, i));
              answer = true;
            }
          }
        }
      }
    }
  }
  std::swap(last_new_configs, new_new_configs);
  return answer;
}