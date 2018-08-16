#pragma once

#include "IGraph.h"

class ListGraph : public IGraph {
public:
    explicit ListGraph(int n);
    explicit ListGraph(const IGraph& other);

    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;

private:
    std::vector<std::vector<int>> adjacencyList;
    bool isValidIndex(int index) const;
};

// ListGraph graph(5);
//
// graph.AddEdge(0, 1);
// graph.AddEdge(0, 2);
// graph.AddEdge(1, 2);
// graph.AddEdge(1, 3);
// graph.AddEdge(3, 4);
//
// for(int v : graph.GetNextVertices(0)) {
//     std::cout << v << ' ';
// }
// std::cout << '\n' << graph.VerticesCount();
