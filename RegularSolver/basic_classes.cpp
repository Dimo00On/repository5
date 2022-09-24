#include "basic_classes.h"

Edge::Edge(Vertex* from, Vertex* to, std::string word) : from(from), to(to), word(std::move(word)) {}

Edge::~Edge() = default;

Vertex::Vertex() = default;

Vertex::Vertex(bool isTerminal) : isTerminal(isTerminal) {}

Vertex::~Vertex() = default;

Edge* Vertex::createEdge(Vertex* to, const std::string& word) {
    Edge* newEdge = new Edge(this, to, word);
    edges.insert(newEdge);
    ++newEdge->to->cntEntering;
    return newEdge;
}

void Vertex::deleteEdge(Edge* edge, bool multiDeleting) {
    --edge->to->cntEntering;
    if (!multiDeleting) {
        edges.erase(edge);
    }
    delete edge;
}

Vertex* Graph::createVertex(bool isTerminal) {
    auto newVertex = new Vertex(isTerminal);
    v.insert(newVertex);
    if (isTerminal) {
        terminal.insert(newVertex);
    }
    return newVertex;
}

void Graph::deleteVertex(Vertex* vertex) {
    if (vertex->isTerminal) {
        terminal.erase(vertex);
    }
    v.erase(vertex);
    for (auto edge : vertex->edges) {
        vertex->deleteEdge(edge, true);
    }
    delete vertex;
}

void Graph::clear() {
    for (auto vertex : v) {
        delete vertex;
    }
}

Graph::Graph(char letter) {
    auto start = createVertex(letter == '1');
    if (letter != '0' && letter != '1') {
        auto end = createVertex(true);
        start->createEdge(end, std::string(1, letter));
    }
    begin = start;
}

Graph::~Graph() = default;

size_t Graph::size() {
    return v.size();
}



/*осталось написать функцию поиска минимального пдкh
*/
