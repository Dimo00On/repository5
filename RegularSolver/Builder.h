#include "basic_classes.h"
#pragma once

class Builder {
public:
    Graph* result = nullptr;
    const std::unordered_set<char>& alphabet;

    Builder(const std::unordered_set<char>& alphabet);
    ~Builder();

    Graph* unite(Graph* first, Graph* second);
    Graph* conjunction(Graph* first, Graph* second);
    Graph* star(Graph* graph);
    Graph* createGraph(char letter);
    void inverseTerminals();
    Graph* createNKA(const std::string& postfixExpr);
};