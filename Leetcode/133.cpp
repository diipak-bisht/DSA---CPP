#include <bits/stdc++.h>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    
    Node* DFSUtil(Node* node, unordered_map<int, Node*> &visited_nodes) {
        auto vn = visited_nodes.find(node->val);
        if(vn == visited_nodes.end()) {
            return vn->second;
        }
        
        Node* cloned_node = new Node(node->val);
        visited_nodes[node->val] = cloned_node;
        for(auto n : node->neighbors) {
            (cloned_node->neighbors).push_back(DFSUtil(n, visited_nodes));
        }
        return cloned_node;
    }
    
    Node* cloneGraph(Node* node) {
        if(node == NULL) {
            return NULL;
        }
        
        unordered_map<int, Node*> visited_nodes;
        return DFSUtil(node, visited_nodes);
       
    }
};

int main() {
    Node graphs[4];
    Node* _1 = new Node(1);
    Node* _2 = new Node(2);
    Node* _3 = new Node(3);
    Node* _4 = new Node(4);
    _1->neighbors.push_back(_2);
    _1->neighbors.push_back(_4);

    _2->neighbors.push_back(_1);
    _2->neighbors.push_back(_3);

    _3->neighbors.push_back(_2);
    _3->neighbors.push_back(_4);

    _4->neighbors.push_back(_1);
    _4->neighbors.push_back(_3);
    Solution sol;
    sol.cloneGraph(_1);
    return 0;
}