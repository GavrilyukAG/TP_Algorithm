#include <vector>
#include <cassert>
#include "MatrixGraph.h"

MatrixGraph::~MatrixGraph() {
    for(int i = 0; i < size; ++i) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

MatrixGraph::MatrixGraph(int n) : size(n) {
    assert(n > 0);
    adjacencyMatrix = new bool*[n];
    for(int i = 0; i < n; ++i) {
        adjacencyMatrix[i] = new bool[n];
    }
}

MatrixGraph::MatrixGraph(const IGraph& other)
    : MatrixGraph(other.VerticesCount())
{
    for(int i = 0; i < other.VerticesCount(); ++i) {
        for(int v : other.GetNextVertices(i)) {
            adjacencyMatrix[i][v] = 1;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    assert(isValidIndex(from));
    assert(isValidIndex(to));

    adjacencyMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return size;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(isValidIndex(vertex));

    std::vector<int> buf;
    for(int i = 0; i < size; ++i) {
        if(adjacencyMatrix[vertex][i] == 1) {
            buf.push_back(i);
        }
    }
    return buf;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(isValidIndex(vertex));

    std::vector<int> buf;
    for(int i = 0; i < size; ++i) {
        if(adjacencyMatrix[i][vertex] == 1) {
            buf.push_back(i);
        }
    }
    return buf;
}

bool MatrixGraph::isValidIndex(int index) const {
    return (index >= 0 && index < size);
}
