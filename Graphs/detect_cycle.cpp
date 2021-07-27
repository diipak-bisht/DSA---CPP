#include "graph.h"
using namespace std;

int V = 4;

enum COLOR {WHITE, BLACK, GRAY};

bool DFS_util(Graph *g, int n, bool *visited, bool *recr_stack) {
    visited[n] = true;
    recr_stack[n] = true;

    auto adj_list = g->all_vertices()[n];
    for(auto adj : adj_list) {
        if(!visited[adj] && DFS_util(g, adj, visited, recr_stack)) {
            return true;
        } else if (recr_stack[adj]) {
            return true;
        }
    }
    recr_stack[n] = false;
    return false;
}

bool is_cyclic(Graph *g) {
    // Do a DFS and check for backedges
    bool *visited = new bool[V];
    bool *recr_stack = new bool[V];
    for(int i=0; i<V; i++) {
        visited[i] = false;
        recr_stack[i] = false;
    }

    for(int i=0; i<V; i++) {
        if(DFS_util(g, i, visited, recr_stack)) {
            return true;
        }
    }
    return false;
}

bool DFS_color_util(Graph *g, int src, int *visited) {
    visited[src] = GRAY;
    
    auto adj_list = g->all_vertices()[src];
    for(int adj : adj_list) {
        if(visited[adj] == GRAY || (visited[adj] == WHITE && DFS_color_util(g, adj, visited))) {
            return true;
        }
    }

    visited[src] = BLACK;
    return false;
}

bool is_cyclic_color_based(Graph *g) {
    // Mark all nodes white
    int *visited = new int[V];
    for(int i=0; i<V; i++) {
        visited[i] = COLOR::WHITE;
    }

    for(int i=0; i<V; i++) {
        if(visited[i] == WHITE && DFS_color_util(g, i, visited)) {
            return true;
        }
    }
    return false;
}

int main() {
    Graph g(V);
    g.addEdge(0, 1);
    // g.addEdge(0, 2);
    g.addEdge(1, 2);
    // g.addEdge(2, 0);
    g.addEdge(2, 3);
    // g.addEdge(3, 3);

    // Approah 1 : Simply doing DFS
    cout<< "Graph cycle detection based on pure DFS\n";
    if (is_cyclic(&g)) {
        cout<< "Graph contains cycle";
    } else {
        cout<< "Graph is acyclic";
    }

    // Approach 2: Using color in DFS where
    /*
        WHITE: node has not been process yet
        GRAY: DFS of node is in progress
        BLACK: DFS of the node is completed
    */
    cout<< "\nGraph cycle detection based on augmented DFS based on colors\n";
    if(is_cyclic_color_based(&g)) {
        cout<< "Graph contains cycle";
    } else {
        cout<< "Graph is acyclic";
    }
    return 0;
}