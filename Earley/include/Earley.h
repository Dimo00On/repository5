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
  std::vector<std::vector<std::set<Rule>>> middle_config_packs;
  std::vector<std::vector<std::set<Rule>>> end_config_packs;
  std::vector<int> word;
  int length;

  void Scan(int step, std::set<Configuration>& new_configs);
  bool Predict(int step, std::set<Configuration>& new_configs);
  bool Complete(int step, std::set<Configuration>& last_new_configs);
};
