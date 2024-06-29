#include "Kruskal.h"
#include <algorithm>
#include <numeric>

Kruskal::Kruskal(const Graph& graph) : graph(graph) {}

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

void Kruskal::run() {
    std::vector<Edge> edges;
    for (int u = 0; u < graph.V; ++u) {
        for (const auto& [v, weight] : graph.adjList[u]) {
            edges.push_back({u, v, weight});
        }
    }

    std::sort(edges.begin(), edges.end());

    std::vector<int> parent(graph.V);
    std::iota(parent.begin(), parent.end(), 0);

    auto find = [&](int u) {
        while (u != parent[u]) {
            u = parent[u];
        }
        return u;
    };

    auto unite = [&](int u, int v) {
        parent[find(u)] = find(v);
    };

    for (const auto& edge : edges) {
        if (find(edge.u) != find(edge.v)) {
            mst.push_back({edge.u, edge.v});
            unite(edge.u, edge.v);
        }
    }
}

void Kruskal::printMST() const {
    std::cout << "Minimalne drzewo rozpinajace (MST) za pomoca algorytmu Kruskala:\n";
    for (const auto& edge : mst) {
        std::cout << edge.first << " - " << edge.second << "\n";
    }
}
