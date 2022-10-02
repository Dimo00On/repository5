#include "Builder.h"

Graph* Builder::unite(Graph* first, Graph* second) {
    bool terminal = first->begin->isTerminal || second->begin->isTerminal;
    auto newBegin = first->createVertex(terminal);
    ++newBegin->cntEntering;
    --first->begin->cntEntering;
    --second->begin->cntEntering;
    for (auto edge : first->begin->edges) {
        newBegin->createEdge(edge->to, edge->word);
    }
    for (auto edge : second->begin->edges) {
        newBegin->createEdge(edge->to, edge->word);
    }
    if (first->begin->cntEntering == 0) {
        first->deleteVertex(first->begin);
    }
    if (second->begin->cntEntering == 0) {
        second->deleteVertex(second->begin);
    }
    first->begin = newBegin;
    first->v.merge(second->v);
    first->terminal.merge(second->terminal);
    delete second;
    return first;
}

Graph* Builder::conjunction(Graph* first, Graph* second) {
    --second->begin->cntEntering;
    for (auto vertex : first->terminal) {
        vertex->isTerminal = second->begin->isTerminal;
        for (auto edge : second->begin->edges) {
            vertex->createEdge(edge->to, edge->word);
        }
        if (vertex->isTerminal) {
            second->terminal.insert(vertex);
        }
    }
    if (second->begin->cntEntering == 0) {
        second->deleteVertex(second->begin);
    }
    std::swap(first->terminal, second->terminal);
    first->v.merge(second->v);
    delete second;
    return first;
}

Graph* Builder::star(Graph* graph) {
    auto newBegin = graph->createVertex(true);
    ++newBegin->cntEntering;
    --graph->begin->cntEntering;
    for (auto edge : graph->begin->edges) {
        newBegin->createEdge(edge->to, edge->word);
    }
    for (auto vertex : graph->terminal) {
        if (vertex == newBegin) {
            continue;
        }
        for (auto edge : newBegin->edges) {
            vertex->createEdge(edge->to, edge->word);
        }
    }
    if (graph->begin->cntEntering == 0) {
        graph->deleteVertex(graph->begin);
    }
    graph->begin = newBegin;
    return graph;
}

Graph* Builder::createGraph(char letter) {
    auto newGraph = new Graph(letter);
    return newGraph;
}

void Builder::inverseTerminals() { //use only for PDKA
    for (auto vertex : result->v) {
        vertex->isTerminal = true;
    }
    for (auto vertex : result->terminal) {
        vertex->isTerminal = false;
    }
    result->terminal.clear();
    for (auto vertex : result->v) {
        if (vertex->isTerminal) {
            result->terminal.insert(vertex);
        }
    }
}

Graph* Builder::createNKA(const std::string& postfixExpr) {
    std::stack<Graph*> graphParts;
    std::set<char> operations = {'+', '.', '*'};
    for (auto i : postfixExpr) {
        if (operations.count(i)) {
            if (i == '*') {
                Graph* lastPart = graphParts.top();
                graphParts.pop();
                graphParts.push(star(lastPart));
            }
            if (i == '.') {
                Graph* second = graphParts.top();
                graphParts.pop();
                Graph* first = graphParts.top();
                graphParts.pop();
                graphParts.push(conjunction(first, second));
            }
            if (i == '+') {
                Graph* second = graphParts.top();
                graphParts.pop();
                Graph* first = graphParts.top();
                graphParts.pop();
                graphParts.push(unite(first, second));
            }
        } else {
            graphParts.push(createGraph(i));
        }
    }
    result = graphParts.top();
    return result;
}

Builder::~Builder() {
    delete result;
}

Builder::Builder(const std::unordered_set<char>& alphabet) : result(nullptr), alphabet(alphabet) {}