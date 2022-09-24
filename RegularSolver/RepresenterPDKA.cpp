#include "RepresenterPDKA.h"

RepresenterPDKA::RepresenterPDKA(Graph* graph) :
size(static_cast<int>(graph->size()) + 1), graph(graph) {
    numberToPtr.resize(size);
    edges.resize(size);
}

void RepresenterPDKA::representPDKA() {
    int cnt = 1;
    graph->mock = graph->createVertex(true);
    graph->begin->number = 1;
    graph->mock->number = 0;
    numberToPtr[1] = graph->begin;
    numberToPtr[0] = graph->mock; //end->0, begin->1, 2, ...
    for (auto vertex : graph->v) {
        if (vertex != graph->begin && vertex != graph->mock) {
            ++cnt;
            numberToPtr[cnt] = vertex;
            vertex->number = cnt;
        }
    }
    for (auto vertex : graph->terminal) {
        if (graph->mock == vertex) {
            continue;
        }
        vertex->isTerminal = false;
        edges[vertex->number][0] = "1";
    }
    for (auto vertex : graph->v) {
        for (auto edge : vertex->edges) {
            int toNumber = static_cast<int>(edge->to->number);
            if (edges[vertex->number].count(toNumber)) {
                (edges[vertex->number][toNumber] += "+") += edge->word;
                //в 0 идут только эпсилон ребра, и они не присутствуют явно в графе
            } else {
                edges[vertex->number][toNumber] = edge->word;
            }
        }
    }
}