#include <iostream>
#include <ctime>
#include "Graph/ArcGraph.cpp"
#include "Graph/ListGraph.cpp"
#include "Graph/MatrixGraph.cpp"
#include "Graph/SetGraph.cpp"


int main() {
    srand(time(0));

    ArcGraph graph(1000);

    for(int i = 0; i < 1000; ++i) {
        graph.AddEdge(i, random() % 1000);
        graph.AddEdge(random() % 1000, i);
        graph.AddEdge(random() % 1000, random() % 1000);
    }

    for(int v : graph.GetNextVertices(random() % 1000)) {
        std::cout << v << ' ';
    }

    std::cout << '\n' << graph.VerticesCount();

    std::cout << '\n' << "Time: " << clock() / 1000.0 << '\n';

    return 0;
}
