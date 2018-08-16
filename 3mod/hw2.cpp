#include <iostream>
#include <queue>
#include "Graph/ListGraph.cpp"

template <class Graph>
int BFScount(const Graph& graph, int from, int to) {
    if(from == to) {
        return 0;
    }

    std::queue<int> graphQ;
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::vector<int> wayTo(graph.VerticesCount(), 0);
    std::vector<int> wayCount(graph.VerticesCount(), 0);

    graphQ.push(from);
    visited[from] = true;
    wayCount[from] = 1;
    // int count = 0;
    while(!graphQ.empty()) {
        int vertex = graphQ.front();
        graphQ.pop();
        // std::cout << vertex << " ";
        for(int v : graph.GetNextVertices(vertex)) {
            if(!visited[v]) {
                graphQ.push(v);
                visited[v] = true;
                wayTo[v] = wayTo[vertex] + 1;
                wayCount[v] = wayCount[vertex];
            } else if(wayTo[v] == wayTo[vertex] + 1) {
                // graphQ.push(v);
                ++wayCount[v];
            }

            // if(v == to && wayTo[to] == wayTo[vertex] + 1) {
            //     ++count;
            // }
        }
    }
    return wayCount[to];
}


int main() {
    int v = 0; // кол-во вершин
    int n = 0; // кол-во ребер
    std::cin >> v >> n;

    ListGraph graph(v);

    int from = 0, to = 0;
    for(int i = 0; i < n; ++i) {
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }

    std::cin >> from >> to;
    std::cout << BFScount(graph, from, to);

    return 0;
}
