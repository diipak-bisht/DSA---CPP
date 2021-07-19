#include "graph.h"

using namespace std;

string get_path(int v, map<int, int> path_to_vertex) {
    string path = to_string(v);
    int parent = path_to_vertex[v];
    while ( parent != -1 ) {
        path = to_string(parent) + "-->" + path;
        parent = path_to_vertex[parent];
    }
    return path;
}

void dijkstra(WeightedGraph *wg) {
    MinHeapMap heap_map;
    map<int, int> path_to_vertex;
    map<int, int> min_distance;
    for(int i = 1; i <= wg->get_vertices(); i++) {
        heap_map.add(i, INT_MAX);
    }
    heap_map.decrease(1, 0);
    min_distance[1] = 0;
    path_to_vertex[1] = -1;

    while(heap_map.size() > 0) {
        auto min_extracted = heap_map.extract_min();
        int root = min_extracted.second;
        // Get adjacency list of the root
        auto adjacency_root = wg->get_edges()[root];
        for(auto adj_root_vertex : adjacency_root) {
            int dist = min_extracted.first + adj_root_vertex.second;
            if(heap_map.contains(adj_root_vertex.first) != -1 && heap_map.get_weight(adj_root_vertex.first) > dist) {
                heap_map.decrease(adj_root_vertex.first, dist);
                min_distance[adj_root_vertex.first] = dist;
                path_to_vertex[adj_root_vertex.first] = root;
            }
        }
    }

    cout<< "Shortest distance to all nodes from 1:\nVertex\tDistance\t\tPath\n";
    for(auto min_d: min_distance) {
        cout<<min_d.first << "\t" << min_d.second << "\t\t" << get_path(min_d.first, path_to_vertex) << "\n";
    }
    // heap_map.print();
}

int main() {
    WeightedGraph wg(9);
    // Constructing Graph
    wg.add_edge(1, 2, 4);
    wg.add_edge(1, 8, 8);
    wg.add_edge(2, 1, 4);
    wg.add_edge(2, 3, 8);
    wg.add_edge(2, 8, 11);
    wg.add_edge(3, 2, 8);
    wg.add_edge(3, 4, 7);
    wg.add_edge(3, 6, 4);
    wg.add_edge(3, 9, 2);
    wg.add_edge(4, 3, 7);
    wg.add_edge(4, 5, 9);
    wg.add_edge(4, 6, 14);
    wg.add_edge(5, 4, 9);
    wg.add_edge(5, 6, 10);
    wg.add_edge(6, 3, 4);
    wg.add_edge(6, 4, 14);
    wg.add_edge(6, 5, 10);
    wg.add_edge(6, 7, 2);
    wg.add_edge(7, 6, 2);
    wg.add_edge(7, 8, 1);
    wg.add_edge(7, 9, 6);
    wg.add_edge(8, 1, 8);
    wg.add_edge(8, 2, 11);
    wg.add_edge(8, 7, 1);
    wg.add_edge(8, 9, 7);
    wg.add_edge(9, 3, 2);
    wg.add_edge(9, 7, 6);
    wg.add_edge(9, 8, 7);

    dijkstra(&wg);
    return 0;
}