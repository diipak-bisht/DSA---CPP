#include <bits/stdc++.h>>
using namespace std;
class Solution {
    
    list<int> courses[10005];
    bool visited[10005];
    bool recr_stack[10005];
    
public:
    
    bool DFS_util(int n) {
        visited[n] = true;
        recr_stack[n] = true;

        auto adj_list = courses[n];
        for(auto adj : adj_list) {
            if(!visited[adj] && DFS_util(adj)) {
                return true;
            } else if (recr_stack[adj]) {
                return true;
            }
        }
        recr_stack[n] = false;
        return false;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Do a DFS and check for backedges
        for(auto prereq : prerequisites) {
            courses[prereq[1]].push_back(prereq[0]);
        }
        for(int i=0; i<numCourses; i++) {
            visited[i] = false;
            recr_stack[i] = false;
        }

        for(int i=0; i<numCourses; i++) {
            if(DFS_util(i)) {
                return false;
            };
        }
        return true;
    }
};