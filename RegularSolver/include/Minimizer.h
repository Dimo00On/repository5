#include "basic_classes.h"
#include "Builder.h"
#pragma once

class Minimizer {
public:
    Builder* builder;
    //Graph* graph;
    const int AlphabetSize;
    const std::unordered_set<char>& alphabet;
    std::unordered_map<Vertex*, std::unordered_map<char, Vertex*>> edges;
    std::vector<std::unordered_set<Vertex*>> classes;

    Minimizer(Builder* builder, const int AlphabetSize, const std::unordered_set<char>& alphabet);
    void restructureEdges();
    void minimize();
    Graph* rebuild();
};
