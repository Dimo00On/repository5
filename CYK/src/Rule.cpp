#include "Rule.h"
#include <utility>

Rule::Rule() = default;
Rule::Rule(int from, std::vector<int> to, int value) : from(from), to(std::move(to)), value(value) {}
Rule::Rule(const Rule& other) = default;
bool Rule::operator<(const Rule& other) const {
  if (from == other.from) {
    return to < other.to;
  }
  return from < other.from;
}
