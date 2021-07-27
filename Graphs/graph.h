#include<bits/stdc++.h>
#include "min_heap_map.h"

class Graph {
    int n;
    bool undirected = false;
    std::vector<std::list<int>> _vertices;

    public:
    Graph(int vertices) {
        n = vertices;
        _vertices.resize(n+1);
    }

    Graph(int vertices, bool undirected) {
        n = vertices;
        this->undirected = undirected;
        _vertices.resize(n+1);
    }

    void addEdge(int u, int v) {
        _vertices[u].push_back(v);
        if(this->undirected) {
            _vertices[v].push_back(u);
        }
        // Maintain vertices
        if (u >= n) {
            n = u;
        }
    }

    void printGraph() {
        int i = 0;
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
    int total_edges = 0;
    std::vector<std::list<std::pair<int, int>>> edges;

    public:
    WeightedGraph(int n) {
        vertices = n;
        edges.resize(n+1);
    }

    void add_edge(int u, int v, int weight) {
        edges[u].push_back(std::make_pair(v, weight));
        total_edges++;
        if (u >= vertices) {
            vertices = u;
        }
    }

    void print_graph() {
        int i = 0;
        while(i <= vertices) {
            std::cout << i;
            for(auto v : edges[i]) {
                std::cout << "-->" << v.first << " (" << v.second<< ")";
            }
            std::cout<<std::endl;
            i++;
        }
    }

    void update_adjacency_list(int src, std::list<std::pair<int, int>> adj_list) {
        edges[src] = adj_list;
    }

    int get_total_edges() {
        return this->total_edges;
    }

    auto get_edges() {
        return edges;
    }

    auto get_vertices() {
        return vertices;
    }

};