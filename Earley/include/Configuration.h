#include "Rule.h"
#pragma once

struct Configuration : Rule {
  int index;

  Configuration();
  Configuration(const Rule& rule, int index);
  Configuration(int from, const std::vector<int>& to, int value, int index);
  //bool operator<(const Configuration& other) const;
};