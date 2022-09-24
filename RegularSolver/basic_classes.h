#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <stack>
#include <cassert>
#include <unordered_map>
#include <vector>
#pragma once

const int AlphabetBegin = 97;
const int AlphabetEnd = 123;

class Vertex;

class Edge {
public:
    Vertex* from;
    Vertex* to;
    std::string word;

    Edge(Vertex* from, Vertex* to, std::string word = "");
    ~Edge();
};

class Vertex {
public:
    bool isTerminal = false;
    std::unordered_set<Edge*> edges;
    int cntEntering = 0;
    uint64_t number = -1;

    Vertex();
    Vertex(bool isTerminal);
    ~Vertex();
    Edge* createEdge(Vertex* to, const std::string& word = "");
    void deleteEdge(Edge* edge, bool multiDeleting = false);
};

class Graph {
public:
    Vertex* begin;
    Vertex* mock = nullptr;
    std::unordered_set<Vertex*> v;
    std::unordered_set<Vertex*> terminal;


    Vertex* createVertex(bool isTerminal = false);
    void deleteVertex(Vertex* vertex);
    void clear();
    explicit Graph(char letter);
    ~Graph();
    size_t size();
};