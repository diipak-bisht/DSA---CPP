#include "graph.h"
using namespace std;

#define V 4

struct vertex_info {
    bool visited;
};

void DFSUtil(int src, Graph *g, vertex_info book_keeping[]) {
    book_keeping[src].visited = true;
    cout<< src<< "\t";
    auto adjacency_list = g->all_vertices()[src];
    for(auto edge : adjacency_list) {
        if(!book_keeping[edge].visited) {
            DFSUtil(edge, g, book_keeping);
        }
    }
}

void dfs(Graph *g) {
    vertex_info vertex_book_keeping[V];
    vertex_info not_vistied;
    not_vistied.visited = false;
    fill_n(vertex_book_keeping, V, not_vistied);
    cout<<"DFS traversal is from 2:\n";
    DFSUtil(2, g, vertex_book_keeping);
    for(int i=0; i<V; i++) {
        if(!vertex_book_keeping[i].visited)
            DFSUtil(i, g, vertex_book_keeping);
    }
}

int main() {
    Graph g(V);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,2);
    g.addEdge(2,0);
    g.addEdge(2,3);
    g.addEdge(3,3);

    dfs(&g);
    return 0;
}