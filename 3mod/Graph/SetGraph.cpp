#include <unordered_set>
#include <vector>
#include <cassert>
#include "SetGraph.h"

SetGraph::SetGraph(int n) : adjacencyHashTable(n) {}

SetGraph::SetGraph(const IGraph& other)
    : adjacencyHashTable(other.VerticesCount())
    {
        for(int i = 0; i < VerticesCount(); ++i) {
            for(int v : other.GetNextVertices(i)) {
                adjacencyHashTable[i].insert(v);
            }
        }
    }

void SetGraph::AddEdge(int from, int to) {
    assert(isValidIndex(from));
    assert(isValidIndex(to));

    adjacencyHashTable[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return adjacencyHashTable.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(isValidIndex(vertex));
    std::vector<int> buf;
    for(int it : adjacencyHashTable[vertex]) {
        buf.push_back(it);
    }
    return buf;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(isValidIndex(vertex));
    std::vector<int> buf;
    for(int i = 0; i < adjacencyHashTable.size(); ++i) {
        for(int v : adjacencyHashTable[i]) {
            if(v == vertex) {
                buf.push_back(v);
            }
        }
    }
    return buf;
}

bool SetGraph::isValidIndex(int index) const {
    return (index >= 0 && index < adjacencyHashTable.size());
}
