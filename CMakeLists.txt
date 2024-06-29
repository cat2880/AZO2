cmake_minimum_required(VERSION 3.27)
project(aizo2)

set(CMAKE_CXX_STANDARD 17)

add_executable(aizo2 main.cpp
        Graph.h
        Prim.h
        Kruskal.h
        Dijkstra.h
        BellmanFord.h
        BellmanFord.cpp
        Dijkstra.cpp
        Kruskal.cpp
        Prim.cpp
        Graph.cpp)
