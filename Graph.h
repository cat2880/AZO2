#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <utility>

class Graph {
public:
    Graph(int vertices, bool isDirected);
    ~Graph();

    void addEdge(int u, int v, int weight);
    void printMatrix() const;
    void printList() const;

    int V;
    bool directed;
    int** matrix; // Dynamiczna macierz incydencji
    std::vector<std::pair<int, int>>* adjList; // Dynamiczna lista sąsiedztwa
};

#endif // GRAPH_H
