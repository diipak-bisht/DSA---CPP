/**
 * The goal is to assign undirected edges, a direction so that the graph will not become cyclic
 * The directed graph initially given is guaranteed to be acyclic
 * */

#include "graph.h"
using namespace std;

int V=6;

void topo_util(Graph *g, int src, bool *visited, unordered_map<int, int> *topo_order) {
    visited[src] = true;
    auto adj_list = g->all_vertices()[src];
    for(auto adj : adj_list) {
        if(!visited[adj]) {
            topo_util(g, adj, visited, topo_order);
        }
    }
    int size = V - topo_order->size() - 1;
    topo_order->insert({src, size});
}

int main() {
    Graph g(V);
    g.addEdge(0, 1);
    g.addEdge(0, 5);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(5, 1);
    g.addEdge(5, 2);

    list<pair<int, int>> undirected_edges;
    undirected_edges.push_back({0,2});
    undirected_edges.push_back({0,3});
    undirected_edges.push_back({4,5});

    unordered_map<int, int> topo_order;
    bool *visited = new bool[V];
    for (int i=0; i<V; i++) {
        visited[i] = false;
    }

    // Get topological sorted order
    for(int i=0; i<V; i++) {
        if(!visited[i]) {
            topo_util(&g, i, visited, &topo_order);
        }
    }

    // Check all the undirected graphs and add a direction based on topo order
    for(auto ue : undirected_edges) {
        if(topo_order[ue.first] < topo_order[ue.second]) {
            g.addEdge(ue.first, ue.second);
        } else {
            g.addEdge(ue.second, ue.first);
        }
    }

    g.printGraph();

    return 0;
}