#include<bits/stdc++.h>

#define INF INT_MAX
#define V 4

using namespace std;

/**
 * All pairs shortest distance and path finding algorithm based on Dynamic programming with O(V^3) complexity
 * 
 * */

void floyd_warshall(int graph[V][V]) {
    int path[V][V], i, j , k;
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            if (graph[i][j] < INF) {
                path[i][j] = i;
                // cout<<i;
            }
            // cout<< "\t";
        }
        // cout<< "\n";
    }

    for(int k = 0; k < V; k++) {
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                // INT_OVERFLOW Check
                if (graph[i][k] == INF || graph[k][j] == INF) {
                    continue;
                }
                int intermediate_vertex_dest = graph[i][k] + graph[k][j];
                if(graph[i][j] > intermediate_vertex_dest) {
                    graph[i][j] = intermediate_vertex_dest;
                    path[i][j] = path[k][j];
                }
            }
        }
    }

    cout<<"All pairs shortes paths:\nsrc,dest\tdist\tpath\n";
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            cout<< i << "," << j << "\t";
            if(graph[i][j] == INF) {
                cout<< "No path exist\n";
            } else {
                cout<< graph[i][j] <<"\t";

                 // Printing path
                int src = i;
                int dest = j;
                string path_str = to_string(j);
                while (dest != src) {
                    dest = path[src][dest];
                    path_str = to_string(dest) + "-->" + path_str;
                }
                cout<<path_str<<"\n";
            }
        }
    }
}

int main() {
    int graph[V][V] = {
        {0, 3, 6, 15},
        {INF, 0, -2, INF},
        {INF, INF, 0, 2},
        {1, INF, INF, 0}
    };
    floyd_warshall(graph);
    return 0;
}