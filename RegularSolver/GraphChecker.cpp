#include "GraphChecker.h"
#include <queue>

bool GraphChecker::isSameGraphs(Minimizer& firstMinimizer, Minimizer& secondMinimizer) {
    std::unordered_map<Vertex*, Vertex*> bijection;
    firstMinimizer.restructureEdges();
    secondMinimizer.restructureEdges();
    auto first = firstMinimizer.builder->result;
    auto second = secondMinimizer.builder->result;
    const auto& alphabet = firstMinimizer.alphabet;
    if (first->v.empty() && second->v.empty()) {
        return true;
    }
    bijection[first->begin] = second->begin;
    if (first->begin->isTerminal != second->begin->isTerminal) {
        return false;
    }
    std::queue<Vertex*> toHandle;
    toHandle.push(first->begin);
    std::unordered_set<Vertex*> handled;
    while (!toHandle.empty()) {
        auto vertex = toHandle.front();
        handled.insert(vertex);
        toHandle.pop();
        for (auto letter : alphabet) {
            auto to = firstMinimizer.edges[vertex][letter];
            auto biTo = secondMinimizer.edges[bijection[vertex]][letter];
            if (to->isTerminal != biTo->isTerminal) {
                return false;
            }
            if (bijection.count(to)) {
                if (bijection[to] != biTo) {
                    return false;
                }
            } else {
                bijection[to] = biTo;
            }
            if (!handled.count(to)) {
                toHandle.push(to);
            }
        }
    }
    return true;
}