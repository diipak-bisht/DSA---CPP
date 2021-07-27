#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

int find(int* parent, int node) {
    while (parent[node] != node)
    {
        parent[node] = parent[parent[node]];
        node = parent[node];
    }
    return node;
}

void _union(int xr, int yr, int* size, int* parent)
{
    if (size[xr] < size[yr])
    {
        parent[xr] = parent[yr];
        size[yr] += size[xr];
    }
    else
    {
        parent[yr] = parent[xr];
        size[xr] += size[yr];
    }
}

void solve() {
    int v, e;
    cin >> v >> e;
    list<int> *adj_list = new list<int>[v+1];
    int p1, p2;
    for(int i=0; i<e; i++) {
        cin >> p1 >> p2;
        adj_list[p1].push_back(p2);
        adj_list[p2].push_back(p1);
    }

    // Using disjoint set to find all connected components with size
    int *parent = new int[v+1];
    int *size = new int[v+1];
    for(int i=1; i<=v; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    int routes = v;
    for (int i=1; i<=v; i++) {
        for(auto adj : adj_list[i]) {
            int x = find(parent, i);
            int y = find(parent, adj);
            if(x != y) {
                _union(x, y, size, parent);
                routes--;
            }
        }
    }

    long long int captains = 1l;
    for(int i=1; i<=v; i++) {
        if( parent[i] == i ) {
            captains = ((captains % MOD) * (size[i] % MOD)) % MOD;
        }
    }


    cout<< routes << " " << captains << "\n";
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}