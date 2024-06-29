#ifndef PRIM_H
#define PRIM_H

#include "Graph.h"
#include <vector>
#include <utility>

class Prim {
public:
    Prim(const Graph& graph);
    void run();
    void printMST() const;

private:
    const Graph& graph;
    std::vector<std::pair<int, int>> mst;
};

#endif // PRIM_H
