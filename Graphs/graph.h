#include<bits/stdc++.h>
#include "min_heap_map.h"

class Graph {
    int n;
    std::vector<std::list<int>> _vertices;

    public:
    Graph(int vertices) {
        n = vertices;
        _vertices.resize(n+1);
    }

    void addEdge(int u, int v) {
        _vertices[u].push_back(v);
    }

    void printGraph() {
        int i = 1;
        while(i <= n) {
            std::cout << i;
            for(auto v : _vertices[i]) {
                std::cout << "-->" << v;
            }
            std::cout<<std::endl;
            i++;
        }
    }

    std::vector<std::list<int>> all_vertices() {
        return _vertices;
    }
};

class WeightedGraph {
    int vertices;
    std::vector<std::list<std::pair<int, int>>> edges;

    public:
    WeightedGraph(int n) {
        vertices = n;
        edges.resize(n+1);
    }

    void add_edge(int u, int v, int weight) {
        edges[u].push_back(std::make_pair(v, weight));
    }

    void print_graph() {
        int i = 1;
        while(i <= vertices) {
            std::cout << i;
            for(auto v : edges[i]) {
                std::cout << "-->" << v.first << " (" << v.second<< ")";
            }
            std::cout<<std::endl;
            i++;
        }
    }

    auto get_edges() {
        return edges;
    }

    auto get_vertices() {
        return vertices;
    }

};