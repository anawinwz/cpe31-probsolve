#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<list>
#define MAXN 100000
using namespace std;
vector<int> adj[MAXN+1];
int n, m;
int deg[MAXN+1];

bool visited[MAXN+1];
int layer[MAXN+1];

void bfs(int s){
  //cout << "bfs("<<s<<")"<<endl;
  for(int i=1;i<=n;i++) {
    //visited[i] = false;
    layer[i] = -1;
  }
  layer[s] = 0;
  list<int> Q;
  Q.push_back(s);
  while(!Q.empty()) {
    int u = Q.front();
    Q.pop_front();
    visited[u] = true;
    //printf("Node %d: Layer %d\n",u,layer[u]);
    for(int d=0;d<deg[u];d++) {
      int v = adj[u][d];
      if(layer[v]==-1) {
        layer[v] = layer[u]+1;
        Q.push_back(v);
      }
    }
  }
}
void read_input(){
  memset(deg, 0, MAXN+1);
  int a, b;
  scanf("%d %d", &n, &m);
  for(int i=0;i<m;i++) {
    scanf("%d %d",&a,&b);

    adj[a].push_back(b);
    deg[a]++;

    adj[b].push_back(a);
    deg[b]++;
  }
}

int main() {
  read_input();
  for(int i=1;i<=n;i++) {
    visited[i] = false;
  }
  int ans = 0;
  for(int i=1;i<=n;i++) {
    if(visited[i]) continue;
    bfs(i);
    ans++;
  }
  printf("%d",ans);
  return 0;
}