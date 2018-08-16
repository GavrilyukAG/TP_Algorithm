#pragma once

#include "IGraph.h"

class SetGraph : public IGraph {
public:
    explicit SetGraph(int n);
    explicit SetGraph(const IGraph& other);

    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;

private:
    std::vector<std::unordered_set<int>> adjacencyHashTable;
    bool isValidIndex(int index) const;
};
