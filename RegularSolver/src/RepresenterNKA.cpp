#include "RepresenterNKA.h"

RepresenterNKA::RepresenterNKA(Graph* graph) : graph(graph) {
    size_t size = graph->size();
    numberToPtr.resize(size);
    edges.resize(size);
}

void RepresenterNKA::representNKA() {
    int cnt = 0;
    for (auto vertex : graph->v) {
        vertex->number = cnt;
        numberToPtr[cnt] = vertex;
        ++cnt;
    }
    for (int i = 0; i < cnt; ++i) {
        for (auto edge: numberToPtr[i]->edges) {
            for (auto letter : edge->word) {
                edges[i][letter].insert(edge->to->number);
            }
        }
    }
}