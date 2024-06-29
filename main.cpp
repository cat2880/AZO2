#include <iostream>
#include <chrono>
#include <random>
#include "Graph.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include <fstream>
#include <cstdlib>

using namespace std::chrono;
using namespace std;

void loadGraphFromFile(Graph& graph) {
    std::ifstream file("graph.txt");
    if (!file) {
        std::cerr << "Nie mozna otworzyc pliku!\n";
        return;
    }

    int u, v, weight;
    while (file >> u >> v >> weight) {
        graph.addEdge(u, v, weight);
    }
}

void generateRandomConnectedGraph(Graph& graph, double density) {
    // Pierwszy krok: generowanie drzewa rozpinającego
    for (int v = 1; v < graph.V; ++v) {
        int u = rand() % v; // Losowy wierzchołek już istniejący w drzewie
        int weight = rand() % 100 + 1;
        graph.addEdge(u, v, weight); // Dodaj krawędź do nowego wierzchołka
        graph.addEdge(v, u, weight); // Graf nieskierowany, więc dodaj krawędź w drugą stronę
    }

    // Drugi krok: dodawanie losowych krawędzi, aby osiągnąć podaną gęstość
    int maxEdges = graph.V * (graph.V - 1) / 2;
    int edgesToGenerate = static_cast<int>(density * maxEdges);

    for (int i = graph.V - 1; i < edgesToGenerate; ++i) {
        int u = rand() % graph.V;
        int v = rand() % graph.V;
        int weight = rand() % 100 + 1;
        graph.addEdge(u, v, weight);
        graph.addEdge(v, u, weight);
    }
}

void displayGraph(const Graph& graph) {
    std::cout << "Macierz incydencji:\n";
    graph.printMatrix();
    std::cout << "\nLista sasiedztwa:\n";
    graph.printList();
}

void executeMSTAlgorithms(Graph& graph) {
    auto start = high_resolution_clock::now();
    std::cout << "Algorytm Prima (Lista sasiedztwa):\n";
    Prim prim1(graph);
    prim1.run();
    prim1.printMST();
    auto end = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end - start);
    std::cout << "Czas wykonania Algorytmu Prima (Lista sasiedztwa): " << duration1.count() << " ms\n";

    start = high_resolution_clock::now();
    std::cout << "\nAlgorytm Kruskala (Lista sasiedztwa):\n";
    Kruskal kruskal1(graph);
    kruskal1.run();
    kruskal1.printMST();
    end = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end - start);
    std::cout << "Czas wykonania Algorytmu Kruskala (Lista sasiedztwa): " << duration2.count() << " ms\n";

    // Pomiar dla macierzy incydencji
    start = high_resolution_clock::now();
    std::cout << "\nAlgorytm Prima (Macierz incydencji):\n";
    Prim prim2(graph);
    prim2.run();
    prim2.printMST();
    end = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(end - start);
    std::cout << "Czas wykonania Algorytmu Prima (Macierz incydencji): " << duration3.count() << " ms\n";

    start = high_resolution_clock::now();
    std::cout << "\nAlgorytm Kruskala (Macierz incydencji):\n";
    Kruskal kruskal2(graph);
    kruskal2.run();
    kruskal2.printMST();
    end = high_resolution_clock::now();
    auto duration4 = duration_cast<milliseconds>(end - start);
    std::cout << "Czas wykonania Algorytmu Kruskala (Macierz incydencji): " << duration4.count() << " ms\n";
}

void executeShortestPathAlgorithms(Graph& graph, int src, int dest) {
    auto start = high_resolution_clock::now();
    std::cout << "Algorytm Dijkstry (Lista sasiedztwa):\n";
    Dijkstra dijkstra1(graph);
    dijkstra1.run(src);
    dijkstra1.printPath(src, dest);
    auto end = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end - start);
    std::cout << "Czas wykonania Algorytmu Dijkstry (Lista sasiedztwa): " << duration1.count() << " ms\n";

    start = high_resolution_clock::now();
    std::cout << "\nAlgorytm Bellmana-Forda (Lista sasiedztwa):\n";
    BellmanFord bellmanFord1(graph);
    bellmanFord1.run(src);
    bellmanFord1.printPath(src, dest);
    end = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end - start);
    std::cout << "Czas wykonania Algorytmu Bellmana-Forda (Lista sasiedztwa): " << duration2.count() << " ms\n";

    // Pomiar dla macierzy incydencji
    start = high_resolution_clock::now();
    std::cout << "\nAlgorytm Dijkstry (Macierz incydencji):\n";
    Dijkstra dijkstra2(graph);
    dijkstra2.run(src);
    dijkstra2.printPath(src, dest);
    end = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(end - start);
    std::cout << "Czas wykonania Algorytmu Dijkstry (Macierz incydencji): " << duration3.count() << " ms\n";

    start = high_resolution_clock::now();
    std::cout << "\nAlgorytm Bellmana-Forda (Macierz incydencji):\n";
    BellmanFord bellmanFord2(graph);
    bellmanFord2.run(src);
    bellmanFord2.printPath(src, dest);
    end = high_resolution_clock::now();
    auto duration4 = duration_cast<milliseconds>(end - start);
    std::cout << "Czas wykonania Algorytmu Bellmana-Forda (Macierz incydencji): " << duration4.count() << " ms\n";
}

// metoda dla 20 operacji
/*void executeMSTAlgorithms1(Graph& graph) {
    double totalTimePrimAdjList = 0;
    double totalTimeKruskalAdjList = 0;
    double totalTimePrimIncMatrix = 0;
    double totalTimeKruskalIncMatrix = 0;

    for (int i = 0; i < 20; ++i) {
        // Lista sąsiedztwa
        auto start = high_resolution_clock::now();
        Prim primAdjList(graph);
        primAdjList.run();
        auto end = high_resolution_clock::now();
        totalTimePrimAdjList += duration_cast<milliseconds>(end - start).count();

        start = high_resolution_clock::now();
        Kruskal kruskalAdjList(graph);
        kruskalAdjList.run();
        end = high_resolution_clock::now();
        totalTimeKruskalAdjList += duration_cast<milliseconds>(end - start).count();

        // Macierz incydencji
        start = high_resolution_clock::now();
        Prim primIncMatrix(graph);
        primIncMatrix.run();
        end = high_resolution_clock::now();
        totalTimePrimIncMatrix += duration_cast<milliseconds>(end - start).count();

        start = high_resolution_clock::now();
        Kruskal kruskalIncMatrix(graph);
        kruskalIncMatrix.run();
        end = high_resolution_clock::now();
        totalTimeKruskalIncMatrix += duration_cast<milliseconds>(end - start).count();
    }

    std::cout << "Algorytm Prima (Lista sasiedztwa): " << totalTimePrimAdjList / 20 << " ms\n";
    std::cout << "Algorytm Kruskala (Lista sasiedztwa): " << totalTimeKruskalAdjList / 20 << " ms\n";
    std::cout << "Algorytm Prima (Macierz incydencji): " << totalTimePrimIncMatrix / 20 << " ms\n";
    std::cout << "Algorytm Kruskala (Macierz incydencji): " << totalTimeKruskalIncMatrix / 20 << " ms\n";
}

void executeShortestPathAlgorithms1(Graph& graph, int src, int dest) {
    double totalTimeDijkstraAdjList = 0;
    double totalTimeBellmanFordAdjList = 0;
    double totalTimeDijkstraIncMatrix = 0;
    double totalTimeBellmanFordIncMatrix = 0;

    for (int i = 0; i < 20; ++i) {
        // Lista sąsiedztwa
        auto start = high_resolution_clock::now();
        Dijkstra dijkstraAdjList(graph);
        dijkstraAdjList.run(src);
        auto end = high_resolution_clock::now();
        totalTimeDijkstraAdjList += duration_cast<milliseconds>(end - start).count();

        start = high_resolution_clock::now();
        BellmanFord bellmanFordAdjList(graph);
        bellmanFordAdjList.run(src);
        end = high_resolution_clock::now();
        totalTimeBellmanFordAdjList += duration_cast<milliseconds>(end - start).count();

        // Macierz incydencji
        start = high_resolution_clock::now();
        Dijkstra dijkstraIncMatrix(graph);
        dijkstraIncMatrix.run(src);
        end = high_resolution_clock::now();
        totalTimeDijkstraIncMatrix += duration_cast<milliseconds>(end - start).count();

        start = high_resolution_clock::now();
        BellmanFord bellmanFordIncMatrix(graph);
        bellmanFordIncMatrix.run(src);
        end = high_resolution_clock::now();
        totalTimeBellmanFordIncMatrix += duration_cast<milliseconds>(end - start).count();
    }

    std::cout << "Algorytm Dijkstry (Lista sasiedztwa): " << totalTimeDijkstraAdjList / 20 << " ms\n";
    std::cout << "Algorytm Bellmana-Forda (Lista sasiedztwa): " << totalTimeBellmanFordAdjList / 20 << " ms\n";
    std::cout << "Algorytm Dijkstry (Macierz incydencji): " << totalTimeDijkstraIncMatrix / 20 << " ms\n";
    std::cout << "Algorytm Bellmana-Forda (Macierz incydencji): " << totalTimeBellmanFordIncMatrix / 20 << " ms\n";
}

void measureAlgorithms(int vertices, double density) {
    Graph graph(vertices, false); // Zakładamy, że generujemy nieskierowany graf
    generateRandomConnectedGraph(graph, density);

    std::cout << "Wierzcholki: " << vertices << ", Getosc: " << density << "\n";

    // MST Algorithms
    executeMSTAlgorithms1(graph);

    // Shortest Path Algorithms
    int src = 0;
    int dest = vertices - 1;
    executeShortestPathAlgorithms1(graph, src, dest);

    std::cout << "\n";
}*/

int main() {
    int problem;
    std::cout << "Wybierz problem:\n1. MST\n2. Najkrotsza sciezka\n";
    std::cin >> problem;

    int vertices;
    std::cout << "Podaj liczbe wierzcholkow: ";
    std::cin >> vertices;

    Graph graph(vertices, false); // Zakładamy, że generujemy nieskierowany graf

    int option;
    std::cout << "Wybierz opcje:\n1. Wczytaj dane z pliku\n2. Wygeneruj graf losowo\n";
    std::cin >> option;

    if (option == 1) {
        loadGraphFromFile(graph);
    } else if (option == 2) {
        double density;
        std::cout << "Podaj gestosc grafu (0-1): ";
        std::cin >> density;
        generateRandomConnectedGraph(graph, density);
    }

    displayGraph(graph);

    if (problem == 1) {
        executeMSTAlgorithms(graph);
    } else if (problem == 2) {
        executeShortestPathAlgorithms(graph, 0, vertices-1);
    }

    return 0;

   //dla analizy
    /*vector<int> vertexCounts = {100, 200, 300, 400, 500, 700, 800};
    vector<double> densities = {0.25, 0.5, 0.99};

    for (int vertices : vertexCounts) {
        for (double density : densities) {
            measureAlgorithms(vertices, density);
        }
    }*/
}
