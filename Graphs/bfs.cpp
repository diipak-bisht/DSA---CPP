#include "graph.h"
using namespace std;

int V = 4;

void bfs(Graph *g, int root) {
    bool *visited = new bool[V];
    queue<int> q;
    for (int i=0; i<V; i++) {
        visited[i] = false;
    }

    cout<<"BFS Traversal order is:\n";
    q.push(root);
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        if(!visited[node]) {
            cout<<node<<"\t";
            visited[node] = true;
            auto adj_list = g->all_vertices()[node];
            for(auto adj : adj_list) {
                q.push(adj);
            }
        }
    }
}

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    bfs(&g, 2);
    return 0;
}