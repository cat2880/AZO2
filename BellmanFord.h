#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "Graph.h"
#include <vector>
#include <limits>

class BellmanFord {
public:
    BellmanFord(const Graph& graph);
    void run(int src);
    void printPath(int src, int dest) const;

private:
    const Graph& graph;
    std::vector<int> dist;
    std::vector<int> parent;
};

#endif