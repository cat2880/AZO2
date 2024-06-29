#include "BellmanFord.h"
#include <limits>
#include <iostream>

BellmanFord::BellmanFord(const Graph& graph) : graph(graph) {}

void BellmanFord::run(int src) {
    dist.assign(graph.V, std::numeric_limits<int>::max());
    parent.assign(graph.V, -1);
    dist[src] = 0;

    for (int i = 0; i < graph.V - 1; ++i) {
        for (int u = 0; u < graph.V; ++u) {
            for (const auto& [v, weight] : graph.adjList[u]) {
                if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
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

void BellmanFord::printPath(int src, int dest) const {
    if (dest == src) {
        std::cout << src << " ";
    } else if (parent[dest] == -1) {
        std::cout << "Brak sciezki do " << dest;
    } else {
        printPath(src, parent[dest]);
        std::cout << dest << " ";
    }
}
