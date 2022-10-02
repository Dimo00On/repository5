#include "BuilderPDKA.h"
#include <queue>

BuilderPDKA::BuilderPDKA(Builder* builder, RepresenterNKA* representer) :
builder(builder), representer(representer) {}

Graph* BuilderPDKA::build() {
    std::unordered_map<uint64_t, Vertex*> numberToPtr;
    Graph* graph = builder->createGraph((builder->result->begin->isTerminal ? '1' : '0'));
    uint64_t size = builder->result->size();
    graph->begin->number = (uint64_t)1 << (builder->result->begin->number);
    std::queue<uint64_t> toHandle;
    std::unordered_set<uint64_t> exist;
    toHandle.push(graph->begin->number);
    numberToPtr[graph->begin->number] = graph->begin;
    graph->mock = graph->createVertex();
    graph->mock->number = 0;
    numberToPtr[0] = graph->mock;
    toHandle.push(0);
    exist.insert(0);
    exist.insert(graph->begin->number);
    while (!toHandle.empty()) {
        uint64_t position = toHandle.front();
        toHandle.pop();
        std::unordered_set<uint64_t> vertexes;
        for (uint64_t i = 0; i < size; ++i) {
            if ((position >> i) & (uint64_t)1) {
                vertexes.insert(i);
            }
        }
        for (auto letter : builder->alphabet) {
            uint64_t newPos = 0;
            bool isTerminal = false;
            for (auto vertex: vertexes) {
                if (!representer->edges[vertex].count(letter)) {
                    representer->edges[vertex][letter] = std::unordered_set<uint64_t>();
                }
                for (auto i : representer->edges[vertex][letter]) {
                    newPos |= ((uint64_t)1 << i);
                    isTerminal |= representer->numberToPtr[i]->isTerminal;
                }
            }
            if (!exist.count(newPos)) {
                numberToPtr[newPos] = graph->createVertex(isTerminal);
                if (isTerminal) {
                    graph->terminal.insert(numberToPtr[newPos]);
                }
                toHandle.push(newPos);
                exist.insert(newPos);
            }
            Vertex* to = numberToPtr[newPos];
            numberToPtr[position]->createEdge(to, std::string(1, letter));
        }
    }
    delete builder->result;
    builder->result = graph;
    return graph;
}