#include <vector>
#include <utility>
#include "ArcGraph.h"

ArcGraph::ArcGraph(int n) : adjacencyArray(), vertexCount(n) {}

ArcGraph::ArcGraph(const IGraph& other)
{
    for(int i = 0; i < other.VerticesCount(); ++i) {
        for(int v : other.GetNextVertices(i)) {
            this->AddEdge(i, v);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    // if(Has(from) == false) {
    //     ++vertexCount;
    // }
    // if(Has(to) == false) {
    //     ++vertexCount;
    // }

    adjacencyArray.push_back(std::make_pair(from, to));
}

// bool ArcGraph::Has(int vertex) const {
//     for(int i = 0; i < adjacencyArray.size(); ++i) {
//         if(adjacencyArray[i].first == vertex || adjacencyArray[i].second == vertex) {
//             return true;
//         }
//     }
//     return false;
// }

int ArcGraph::VerticesCount() const {
    return vertexCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {std::vector<int> buf;
    for(int i = 0; i < adjacencyArray.size(); ++i) {
        if(adjacencyArray[i].first == vertex) {
            buf.push_back(adjacencyArray[i].second);
        }
    }
    return buf;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {std::vector<int> buf;
    for(int i = 0; i < adjacencyArray.size(); ++i) {
        if(adjacencyArray[i].second == vertex) {
            buf.push_back(adjacencyArray[i].first);
        }
    }
    return buf;
}
