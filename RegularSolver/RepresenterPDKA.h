#include "basic_classes.h"
#include "RegularExpression.h"
#pragma once

class RepresenterPDKA {
public:
    int size;
    Graph* graph;
    std::vector<Vertex*> numberToPtr;
    std::vector<std::unordered_map<int, RegularExpression>> edges;

    explicit RepresenterPDKA(Graph* graph);
    void representPDKA();
};
