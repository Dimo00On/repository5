#include "BuilderPDKA.h"
#include <queue>

BuilderPDKA::BuilderPDKA(Builder* builder, RepresenterNKA* representer) :
builder(builder), representer(representer) {}

Graph* BuilderPDKA::build() {
    std::vector<Vertex*> numberToPtr(2);
    Graph* graph = builder->createGraph((builder->result->begin->isTerminal ? '1' : '0'));
    int cnt = 1;
    graph->begin->number = 1;
    std::queue<uint64_t> toHandle;
    std::map<std::set<uint64_t>, uint64_t> exist;
    std::vector<std::set<uint64_t>> numberToSet;
    numberToSet.emplace_back();
    numberToSet.push_back({builder->result->begin->number});
    exist[{}] = 0;
    exist[{builder->result->begin->number}] = cnt;
    ++cnt;
    graph->mock = graph->createVertex();
    graph->mock->number = 0;
    numberToPtr[graph->begin->number] = graph->begin;
    numberToPtr[0] = graph->mock;
    toHandle.push(1);
    toHandle.push(0);
    while (!toHandle.empty()) {
        auto position = toHandle.front();
        toHandle.pop();
        auto vertexes = numberToSet[position];
        for (auto letter : builder->alphabet) {
            std::set<uint64_t> newPos;
            bool isTerminal = false;
            for (auto vertex: vertexes) {
                if (!representer->edges[vertex].count(letter)) {
                    representer->edges[vertex][letter] = std::unordered_set<uint64_t>();
                }
                for (auto i : representer->edges[vertex][letter]) {
                    newPos.insert(i);
                    isTerminal |= representer->numberToPtr[i]->isTerminal;
                }
            }
            if (!exist.count(newPos)) {
                numberToPtr.push_back(graph->createVertex(isTerminal));
                numberToPtr[cnt]->number = cnt;
                numberToSet.push_back(newPos);
                if (isTerminal) {
                    graph->terminal.insert(numberToPtr[cnt]);
                }
                toHandle.push(cnt);
                exist[newPos] = cnt;
                ++cnt;
            }
            Vertex* to = numberToPtr[exist[newPos]];
            numberToPtr[position]->createEdge(to, std::string(1, letter));
        }
    }
    delete builder->result;
    builder->result = graph;
    return graph;
}