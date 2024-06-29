#include "Graph.h"

Graph::Graph(int vertices, bool isDirected) : V(vertices), directed(isDirected) {
    // Dynamiczna alokacja macierzy incydencji
    matrix = new int*[V];
    for (int i = 0; i < V; ++i) {
        matrix[i] = new int[V]{0};
    }

    // Dynamiczna alokacja listy sąsiedztwa
    adjList = new std::vector<std::pair<int, int>>[V];
}

Graph::~Graph() {
    // Dealokacja pamięci macierzy incydencji
    for (int i = 0; i < V; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Dealokacja pamięci listy sąsiedztwa
    delete[] adjList;
}

void Graph::addEdge(int u, int v, int weight) {
    matrix[u][v] = weight;
    adjList[u].emplace_back(v, weight);
    if (!directed) {
        matrix[v][u] = weight;
        adjList[v].emplace_back(u, weight);
    }
}


void Graph::printMatrix() const {
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::printList() const {
    for (int i = 0; i < V; ++i) {
        std::cout << i << ": ";
        for (const auto& [v, weight] : adjList[i]) {
            std::cout << "(" << v << ", " << weight << ") ";
        }
        std::cout << std::endl;
    }
}
