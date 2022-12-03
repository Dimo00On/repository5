#include "Configuration.h"
#include <unordered_map>
#include <unordered_set>
#include <set>

class Earley {
public:
  Earley();
  void Create(std::unordered_set<Rule*>& new_rules, int new_start);
  bool Check(const std::vector<int>& word);

protected:
  int start;
  std::unordered_map<int, std::vector<Rule>> rules;
  std::vector<std::unordered_map<int, std::set<Rule>>> middle_config_packs;
  std::vector<std::unordered_map<int, std::set<Rule>>> end_config_packs;
  std::vector<int> word;

  void Scan(int step, std::set<Configuration>& new_configs);
  void Predict(int step, std::set<Configuration>& new_configs);
  void Complete(int step, std::set<Configuration>& last_new_configs);
};
