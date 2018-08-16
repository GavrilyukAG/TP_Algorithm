#pragma once

#include "IGraph.h"

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int n);
    explicit ArcGraph(const IGraph& other);

    void AddEdge(int from, int to);
    int VerticesCount() const;
    bool Has(int vertex) const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;

private:
    std::vector <std::pair <int, int> > adjacencyArray;
    int vertexCount;
};
