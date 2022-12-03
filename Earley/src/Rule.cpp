#include "Rule.h"
#include <utility>

Rule::Rule() = default;
Rule::Rule(int from, const std::vector<int>& to, int value) : from(from), to(to), value(value) {}
Rule::Rule(const Rule& other) = default;
bool Rule::operator<(const Rule& other) const {
  if (from == other.from) {
    if (value == other.value) {
      return to < other.to;
    }
    return value < other.value;
  }
  return from < other.from;
}
