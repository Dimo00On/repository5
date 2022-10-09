#include "Minimizer.h"

Minimizer::Minimizer(Builder* builder, const int AlphabetSize, const std::unordered_set<char>& alphabet) :
                     builder(builder), AlphabetSize(AlphabetSize), alphabet(alphabet) {
    classes.resize(2);
}

void Minimizer::restructureEdges() {
    for (auto vertex : builder->result->v) {
        for (auto edge : vertex->edges) {
            edges[vertex][edge->word[0]] = edge->to;
        }
    }
}

void Minimizer::minimize() {
    restructureEdges();
    int lastClass = 0;
    for (auto vertex : builder->result->v) {
        vertex->number = !vertex->isTerminal;
        classes[!vertex->isTerminal].insert(vertex);
        lastClass |= !vertex->isTerminal;
    }
    if (lastClass == 0) {
        classes.pop_back();
    }
    while (true) {
        for (int i = static_cast<int>(classes.size()) - 1; i >= 0; --i) {
            if (classes[i].size() == 1) {
                (*classes[i].begin())->newNumber = i;
                continue;
            }
            std::map<std::vector<int>, int> tuples;
            for (auto vertex : classes[i]) {
                std::vector<int> newEdgeTuple(AlphabetSize);
                int j = 0;
                for (auto letterIt = alphabet.begin(); letterIt != alphabet.end(); ++letterIt, ++j) {
                    newEdgeTuple[j] = static_cast<int>(edges[vertex][*letterIt]->number);
                }
                if (tuples.empty()) {
                    tuples.emplace(newEdgeTuple, i);
                    vertex->newNumber = i;
                    continue;
                }
                auto tupleIt = tuples.find(newEdgeTuple);
                if (tupleIt != tuples.end()) {
                    vertex->newNumber = tupleIt->second;
                } else {
                    tuples.emplace(newEdgeTuple, classes.size());
                    vertex->newNumber = static_cast<int>(classes.size());
                    classes.emplace_back();
                }
            }
            for (auto vertexIt = classes[i].begin(); vertexIt != classes[i].end();) {
                auto vertex = (*vertexIt);
                if (vertex->newNumber != i) {
                    classes[vertex->newNumber].insert(vertex);
                    auto temp = vertexIt;
                    ++vertexIt;
                    classes[i].erase(temp);
                    continue;
                }
                ++vertexIt;
            }
        }
        if (classes.size() == lastClass + 1) {
            break;
        }
        lastClass = static_cast<int>(classes.size()) - 1;
        for (auto& clas : classes) {
            for (auto vertex : clas) {
                vertex->number = vertex->newNumber;
            }
        }
    }
}

Graph* Minimizer::rebuild() {
    Builder temp(alphabet);
    auto graph = temp.createGraph('0');
    temp.result = graph;
    graph->begin->number = -1;
    std::vector<Vertex*> numberToPtr(classes.size());
    for (int i = 0; i < classes.size(); ++i) {
        auto newVertex = graph->createVertex();
        newVertex->number = i;
        numberToPtr[i] = newVertex;
        for (auto vertex : classes[i]) {
            if (builder->result->begin == vertex) {
                graph->deleteVertex(newVertex);
                graph->begin->number = i;
                numberToPtr[i] = graph->begin;;
            }
        }
    }
    for (int i = 0; i < classes.size(); ++i) {
        auto prevVertex = (*classes[i].begin());
        if (prevVertex->isTerminal) {
            numberToPtr[i]->isTerminal = true;
            graph->terminal.insert(numberToPtr[i]);
        }
        for (auto edge : prevVertex->edges) {
            numberToPtr[i]->createEdge(numberToPtr[edge->to->number], edge->word);
        }
    }
    std::swap(temp.result, builder->result);
    return builder->result;
}