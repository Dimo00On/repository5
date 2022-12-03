#include <vector>
#include <unordered_set>
#pragma once

struct Rule {
  //A->bCD <==> from = A, bCD = vector; terminals < 0, non-terminals > 0
  int from = 0;
  std::vector<int> to;
  //std::unordered_set<int> set;
  int value = 0;

  Rule();
  Rule(int from, std::vector<int>  to, int value = 0);
  Rule(const Rule& other);
  bool operator<(const Rule& other) const;
};

