#include "Configuration.h"

Configuration::Configuration() = default;

Configuration::Configuration(const Rule& rule, int index) : Rule(rule), index(index) {}

Configuration::Configuration(int from, const std::vector<int>& to, int value, int index) :
  Rule(from, to, value), index(index) {}

/*bool Configuration::operator<(const Configuration& other) const {
  if (index == other.index) {
    return rule < other.rule;
  }
  return index < other.index;
}*/