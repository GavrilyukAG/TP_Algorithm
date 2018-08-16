#pragma once

#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int n);
    explicit MatrixGraph(const IGraph& other);
    ~MatrixGraph();

    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;

private:
    bool** adjacencyMatrix;
    int size;

    bool isValidIndex(int index) const;
};
