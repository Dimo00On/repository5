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
  int length = static_cast<int>(word.size());
  end_config_packs.clear();
  middle_config_packs.clear();
  end_config_packs.resize(length + 1);
  middle_config_packs.resize(length + 1);
  middle_config_packs[0][0].insert(rules[0][0]);
  bool changing = true;
  std::set<Configuration> new_configs;
  while (changing) {
    size_t size = middle_config_packs[0].size() + end_config_packs[0].size();
    Predict(0, new_configs);
    Complete(0, new_configs);
    if (middle_config_packs[0].size() + end_config_packs[0].size() == size) {
      changing = false;
    }
  }
  for (int i = 1; i <= length; ++i) {
    Scan(i - 1, new_configs);
    changing = true;
    while (changing) {
      size_t size = middle_config_packs[i].size() + end_config_packs[i].size();
      Predict(i, new_configs);
      Complete(i, new_configs);
      if (middle_config_packs[i].size() + end_config_packs[i].size() == size) {
        changing = false;
      }
    }
  }
  auto it = end_config_packs[length][0].find(Rule(0, {start}, 1));
  if (it == end_config_packs[length][0].end()) {
    return false;
  }
  return true;
}

void Earley::Scan(int step, std::set<Configuration>& new_configs) {
  for (auto& pack : middle_config_packs[step]) {
    for (auto& config : pack.second) {
      if (config.to[config.value] == word[step]) {
        Rule new_config(config.from, config.to, config.value + 1);
        if (config.value + 1 < static_cast<int>(config.to.size())) {
          middle_config_packs[step + 1][pack.first].insert(new_config);
        } else {
          auto it = end_config_packs[step + 1][pack.first].find(new_config);
          if (it == end_config_packs[step + 1][pack.first].end()) {
            end_config_packs[step + 1][pack.first].insert(new_config);
            new_configs.insert(Configuration(new_config, pack.first));
          }
        }
      }
    }
  }
}

void Earley::Predict(int step, std::set<Configuration>& new_configs) {
  for (auto& pack : middle_config_packs[step]) {
    for (auto& config : pack.second) {
      if (config.to[config.value] > 0) {
        for (auto &rule: rules[config.to[config.value]]) {
          Rule new_rule(rule.from, rule.to, 0);
          if (!rule.to.empty()) {
            middle_config_packs[step][step].insert(new_rule);
          } else {
            auto it = end_config_packs[step][step].find(new_rule);
            if (it == end_config_packs[step][step].end()) {
              end_config_packs[step][step].insert(new_rule);
              new_configs.insert(Configuration(rule, step));
            }
          }
        }
      }
    }
  }
}

void Earley::Complete(int step, std::set<Configuration>& last_new_configs) {
  std::set<Configuration> new_new_configs;
  for (auto& end_config : end_config_packs[step][step]) {
    for (auto& pack : middle_config_packs[step]) {
      for (auto& config : pack.second) {
        if (config.to[config.value] == end_config.from) {
          Rule new_config(config.from, config.to, config.value + 1);
          if (config.value + 1 < static_cast<int>(config.to.size())) {
            middle_config_packs[step][pack.first].insert(new_config);
          } else {
            auto it = end_config_packs[step][pack.first].find(new_config);
            if (it == end_config_packs[step][pack.first].end()) {
              end_config_packs[step][pack.first].insert(new_config);
              new_new_configs.insert(Configuration(new_config, pack.first));
            }
          }
        }
      }
    }
  }
  for (auto& end_config : last_new_configs) {
    for (auto& pack : middle_config_packs[end_config.index]) {
      for (auto& config : pack.second) {
        if (config.to[config.value] == end_config.from) {
          Rule new_config(config.from, config.to, config.value + 1);
          if (config.value + 1 < static_cast<int>(config.to.size())) {
            middle_config_packs[step][pack.first].insert(new_config);
          } else {
            auto it = end_config_packs[step][pack.first].find(new_config);
            if (it == end_config_packs[step][pack.first].end()) {
              end_config_packs[step][pack.first].insert(new_config);
              new_new_configs.insert(Configuration(new_config, pack.first));
            }
          }
        }
      }
    }
  }
  std::swap(last_new_configs, new_new_configs);
}