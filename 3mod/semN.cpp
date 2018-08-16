#include <vector>
#include <cassert>
#include <iostream>
#include <queue>

template <class To, class From>
To to(From from) {
    To to = static_cast<To>(from);
    assert(static_cast<int> == from);
    return to;
}

struct IGraph {
virtual ~IGraph() {}

    // Добавление ребра от from к to.
virtual void AddEdge(int from, int to) = 0;

virtual int VerticesCount() const = 0;

virtual std::vector<int> vertices GetNextVertices(int vertex) const = 0;
virtual std::vector<int> vertices GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    explicit ListGraph(int n) : adjancencyList(n) {}
    explicit ListGraph(const IGraph& other);

    virtual void AddEdge(int from, int to) override {
        // assert(isValidIndex(to));
        // assert(isValidIndex(from));

        adjancencyList[from].push_back(to);
        adjancencyList[to].push_back(from);
    }

    virtual int VerticesCount() const  override {
        return to<int> adjancencyList.size();
    }

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjancencyList;

    bool isValidIndex(int index) {
        return (0 <= index && index < to<int>(adjancencyList.size()) );
    }
};

ListGraph::ListGraph(const IGraph& other)
    : ListGraph(other.VerticesCount())
    {
        for(int i = 0; i < /*to<int>*/(adjancencyList.size()); ++i) {
            adjancencyList[i] = other.GetNextVertices(i);
        }
    }

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    return adjancencyList[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    return GetPrevVertices(vertex);
}


// template <class TFunc>
// void BFS(const IGraph* graph, int start, TFunc operation) {
//     std::queue<int> q;
//     std::vector<bool> isVisited(graph.VerticesCount(), false);
//
//     q.push(start);
//     isVisited[start] = true;
//     while(!q.empty()) {
//         int v = q.front();
//         q.pop();
//         operation(q);
//         for(int next : graph.GetNextVertices(v)) {
//             if(!isVisited[next]) {
//                 q.push(next);
//                 isVisited
//             }
//         }
//
//     }
// }

int main() {
    ListGraph graph(5);

    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(3, 4);

    for(int v : graph.GetNextVertices(3)) {
        std::cout << v << ' ';
    }

    return 0;
}
