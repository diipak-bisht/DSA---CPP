#include <bits/stdc++.h>
using namespace std;

int g[1001][1001];
int N,M;
int *parent;
int *size;


int main() {
    cin>>N>>M;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cin>>g[i][j];
        }
    }

    parent = new int[N+1];
    // size = new int[N+1];

    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cout<< g[i][j] <<"\t";
        }
        cout<<"\n";
    }
    return 0;
}