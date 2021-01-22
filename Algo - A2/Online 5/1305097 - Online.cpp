#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <list>
#include <queue>

using namespace std;
#define   read(x)     freopen(x, "r", stdin)
#define   write(x)    freopen(x, "w", stdout)

#define NEG_INFINITE -99999999
#define INFINITE 99999999

#define MAX_NVERTEX 1000
#define WHITE 0
#define GRAY 1
#define BLACK 2

class Graph{
    int nVertices;
    list<int> adjList[MAX_NVERTEX];
    int color[MAX_NVERTEX];
public:
    Graph(int n){
        nVertices = n;
    }
    void addEdge(int u, int v){
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    bool hasST(int s){
        for(int i = 0 ; i < nVertices; i++){
            color[i] = WHITE;
        }
        dfs(s);
        for(int i = 0; i < nVertices; i++){
            if(color[i] == WHITE) return false;
        }
        return true;
    }
    void dfs(int u){ //dfs was unnessary. because we can determine whether a graph is connected using bfs
        color[u] = GRAY;
        list<int>::iterator it;
        it = adjList[u].begin();
        for(;it != adjList[u].end(); it++){
            if(color[*it] == WHITE){
                dfs(*it);
            }
        }
    }
    void bfs(int s){
        int d[MAX_NVERTEX];
        int p[MAX_NVERTEX];

        for(int i = 0 ; i < nVertices; i++){
            color[i]= WHITE;
            d[i] = INFINITE;
            p[i] = -1;
        }

        queue<int>q;
        q.push(s);
        color[s] = GRAY;
        p[s] = -1;
        d[s] = 0;
        while(!q.empty()){
            int u = q.front();
            q.pop();

            list<int>::iterator it;
            it = adjList[u].begin();
            for(;it != adjList[u].end(); it++){
                if(color[*it] == WHITE){
                    q.push(*it);
                    color[*it] = GRAY;
                    p[*it] = u;
                    d[*it] = d[u] + 1;
                }
            }
            color[u] = BLACK;
        }

        cout<<endl<<"distances :\n";
        for(int i = 0 ; i < nVertices; i++){
            cout<<i<<":"<<d[i]<<" ";
        }

        cout<<endl<<"Parent :\n";
        for(int i = 0 ; i < nVertices; i++){
            cout<<i<<":"<<p[i]<<" ";
        }

    }

};
int main(){
    read("input.txt");
    int n, e;
    cin>>n>>e;
    Graph g(n);
    for(int i = 0; i < e; i++){
        int u, v;
        cin>>u>>v;
        g.addEdge(u, v);
    }
    cout<<g.hasST(0)<<endl;
    g.bfs(0);

    return 0;
}



