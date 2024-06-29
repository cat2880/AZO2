#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include <vector>
#include <utility>

class Dijkstra {
public:
    Dijkstra(const Graph& graph);
    void run(int src);
    void printPath(int src, int dest) const;

private:
    const Graph& graph;
    std::vector<int> dist;
    std::vector<int> parent;
};

#endif // DIJKSTRA_H
