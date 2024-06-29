#include "Prim.h"
#include <queue>
#include <functional>
#include <vector>
#include <limits>

Prim::Prim(const Graph& graph) : graph(graph) {}

void Prim::run() {
    int src = 0;
    std::vector<int> key(graph.V, std::numeric_limits<int>::max());
    std::vector<int> parent(graph.V, -1);
    std::vector<bool> inMST(graph.V, false);

    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

    pq.push({0, src});
    key[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto [v, weight] : graph.adjList[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < graph.V; ++i) {
        mst.push_back({parent[i], i});
    }
}

void Prim::printMST() const {
    std::cout << "Minimalne drzewo rozpinajace (MST) za pomoca algorytmu Prima:\n";
    for (const auto& edge : mst) {
        std::cout << edge.first << " - " << edge.second << "\n";
    }
}
