#include<bits/stdc++.h>

class MinHeapMap {
    std::vector<std::pair<int, int>> min_heap;
    std::map<int, int> vertex_position;

    // Add, Decrease, extract_min, contains
    public:
    void add(int u, int weight) {
        min_heap.push_back(std::make_pair(weight, u));
        int current_index = min_heap.size() - 1;
        int parent_index = (current_index - 1) / 2;
        while(parent_index < current_index && parent_index >= 0) {
            int parent_weight = min_heap[parent_index].first;
            if (parent_weight > weight) {
                min_heap[current_index].first = parent_weight;
                min_heap[parent_index].first = weight;
                current_index = parent_index;
                parent_index = (current_index - 1) / 2;
            } else {
                break;
            }
        }
        vertex_position.insert(std::make_pair(u, current_index));
    }

    int contains(int u) {
        auto itr = vertex_position.find(u);
        if(itr == vertex_position.end()) {
            return -1;
        } else {
            return itr->second;
        }
    }

    auto extract_min() {
        auto min = min_heap[0];
        int index = 0;
        int size = min_heap.size();
        min_heap[0] = min_heap[size-1];
        min_heap.pop_back();
        vertex_position.erase(min.second);
        int last_parent = (size - 1) / 2;
        while (index <= last_parent) {
            int left = (2 * index) + 1;
            int right = (2 * index) + 2;
            int index_compare = min_heap[left].first < min_heap[right].first ? left : right;
            if(min_heap[index].first > min_heap[index_compare].first) {
                auto t = min_heap[index];
                min_heap[index] = min_heap[index_compare];
                min_heap[index_compare] = t;
                // Update positions
                vertex_position[min_heap[index].second] = index;
                vertex_position[min_heap[index_compare].second] = index_compare;
                index = index_compare;
            } else {
                break;
            }
        }
        return min;
    }

    int get_weight(int u) {
        int index = vertex_position.find(u)->second;
        return min_heap[index].first;
    }

    void decrease(int u, int weight) {
        int index = vertex_position.find(u)->second;
        min_heap[index].first = weight;
        int parent_index = (index - 1) / 2;
        while (index > 0 && min_heap[parent_index].first > weight) {
            auto t = min_heap[index];
            min_heap[index] = min_heap[parent_index];
            min_heap[parent_index] = t;
            // Update positions
            vertex_position[min_heap[index].second] = index;
            vertex_position[min_heap[parent_index].second] = parent_index;
            index = parent_index;
            parent_index = (index - 1) / 2;
        }
    }

    void print() {
        for(auto heap: min_heap) {
            std::cout<< heap.first << " (" << heap.second << ")\t";
        }
    }

    int size() {
        return min_heap.size();
    }
};