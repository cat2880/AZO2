#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Graph.h"
#include <vector>
#include <utility>

class Kruskal {
public:
    Kruskal(const Graph& graph);
    void run();
    void printMST() const;

private:
    const Graph& graph;
    std::vector<std::pair<int, int>> mst;
};

#endif // KRUSKAL_H
