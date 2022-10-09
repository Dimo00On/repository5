#include "basic_classes.h"
#pragma once

class RepresenterNKA {
public:
    Graph* graph;
    std::vector<Vertex*> numberToPtr;
    std::vector<std::unordered_map<char, std::unordered_set<uint64_t>>> edges;

    explicit RepresenterNKA(Graph* graph);
    void representNKA();
};
