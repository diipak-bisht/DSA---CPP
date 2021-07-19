#include "graph.h"
using namespace std;

#define INF INT_MAX

int V = 5;

void bellman_ford(WeightedGraph *wg) {
    // Initialization
    vector<int> dist, path;
    dist.reserve(V);
    path.reserve(V);

    int source = 0;

    for(int i = 0; i< V; i++) {
        if(i == source) {
            dist[i] = 0;
            path[i] = -1;
        } else {
            dist[i] = INF;
            path[i] = i;
        }
    }

    // V-1 rounds to relax the edges aftre looping over all the edges
    for(int i = 0; i < V-1; i++ ) {
        int src = 0, dest, weight;

        // Below 2 loops are actually running only E times
        for(auto adjacent_vertices : wg->get_edges()) {
            for (auto edge: adjacent_vertices) {
                dest = edge.first;
                weight = edge.second;

                // relax the edge
                if(dist[src] != INF && dist[dest] > dist[src] + weight) {
                    dist[dest] = dist[src] + weight;
                    path[dest] = src;
                }
            }
            src++;
        }
    }

    // Check negative cycles, loop through all edges once more and if any edge can again be relaxed that mean , negative weight cycle has been found
    int src = 0, dest, weight;
    for(auto adjacent_vertices : wg->get_edges()) {
        for (auto edge: adjacent_vertices) {
            dest = edge.first;
            weight = edge.second;

            // relax the edge
            if(dist[src] != INF && dist[dest] > dist[src] + weight) {
                cout<< "Negative Weight Cycle found";
                return;
            }
        }
        src++;
    }

    // Print the distance
    cout<<"Shortest Path from Source Vertex " << source << "\n";
    for(int i = 0; i< V; i++) {
        if(dist[i] == INF) {
            cout<< i << "\tNo path exist\n";
        } else {
            cout<< i << "\t" << dist[i]<< "\t";
            // Printing path
            string path_str = to_string(i);
            int parent = path[i];
            while ( parent != -1 ) {
                path_str = to_string(parent) + "-->" + path_str;
                parent = path[parent];
            }
            cout<< path_str<< "\n";
        }
    }
}

int main() {
    WeightedGraph wg(V);
    wg.add_edge(0, 1, -1);
    wg.add_edge(0, 2, 4);
    wg.add_edge(1, 2, 3);
    wg.add_edge(1, 3, 2);
    wg.add_edge(1, 4, 2);
    wg.add_edge(3, 2, 5);
    wg.add_edge(3, 1, 1);
    wg.add_edge(4, 3, -3);

    bellman_ford(&wg);

    return 0;
}