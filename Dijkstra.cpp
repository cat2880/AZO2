#include "Dijkstra.h"
#include <queue>
#include <limits>
#include <iostream>

Dijkstra::Dijkstra(const Graph& graph) : graph(graph) {}

void Dijkstra::run(int src) {
    dist.assign(graph.V, std::numeric_limits<int>::max());
    parent.assign(graph.V, -1);

    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& [v, weight] : graph.adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    for (int i = 0; i < graph.V; ++i) {
        if (i != src) {
            std::cout << "Najkrotsza sciezka z " << src << " do " << i << ": ";
            printPath(src, i);
            std::cout << "\nDlugosc: " << dist[i] << "\n";
        }
    }
}



void Dijkstra::printPath(int src, int dest) const {
    if (dest == src) {
        std::cout << src << " ";
    } else if (parent[dest] == -1) {
        std::cout << "Brak sciezki do " << dest;
    } else {
        printPath(src, parent[dest]);
        std::cout << dest << " ";
    }
}
