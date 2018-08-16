#include <vector>
#include <cassert>
#include "ListGraph.h"

ListGraph::ListGraph(int n) : adjacencyList(n) {}

ListGraph::ListGraph(const IGraph& other)
    : ListGraph(other.VerticesCount())
{
    for(int i = 0; i < adjacencyList.size(); ++i) {
        adjacencyList[i] = other.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    assert(isValidIndex(from));
    assert(isValidIndex(to));

    adjacencyList[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjacencyList.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(isValidIndex(vertex));
    return adjacencyList[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(isValidIndex(vertex));
    std::vector<int> buf;
    for(int i = 0; i < adjacencyList.size(); ++i) {
        for(int v : adjacencyList[i]) {
            if(v == vertex) {
                buf.push_back(v);
            }
        }
    }
    return buf;
}

bool ListGraph::isValidIndex(int index) const {
    return (index >= 0 && index < adjacencyList.size());
}
