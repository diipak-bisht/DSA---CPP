#include "graph.h"
using namespace std;

void topo_sort_util(int v, Graph *g, set<int> *visited, deque<int> *topo_order) {
    list<int> adjacent_vertices = g->all_vertices()[v];
    visited->insert(v);
    if (adjacent_vertices.size() == 0) {
        topo_order->emplace_front(v);
    } else {
        for(auto vertex : adjacent_vertices) {
            if(visited->find(vertex) == visited->end()) {
                topo_sort_util(vertex, g, visited, topo_order);
            }
        }
        topo_order->emplace_front(v);
    }
}

void topo_sort(Graph *g) {
    set<int> visited;
    deque<int> topo_order;

    int i = 0;
    for(auto adjacent_vertices : g->all_vertices()) {
        if(visited.find(i) == visited.end() && i > 0){
            topo_sort_util(i, g, &visited, &topo_order);
        }
        i++;
    }
    
    for(auto order: topo_order) {
        cout<< order << " ";
    }
}

int main() {
    Graph g(7);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(2, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 6);
    g.addEdge(6, 7);

    topo_sort(&g);

    cout<< "Exiting";
    return 0;
}