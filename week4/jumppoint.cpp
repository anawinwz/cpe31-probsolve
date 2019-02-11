#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<vector>
#include<list>
#include<utility>
#define MAXN 1002
using namespace std;
pair<int,int> node[MAXN+1];
vector<int> adj[MAXN+1];
int n, r, ans = -1;
int deg[MAXN+1];

bool visited[MAXN+1];
int layer[MAXN+1];

void bfs(int s){
  //cout << "bfs("<<s<<")"<<endl;
  for(int i=1;i<=n+1;i++) {
    visited[i] = false;
    layer[i] = -1;
  }
  layer[s] = 0;
  list<int> Q;
  Q.push_back(s);
  while(!Q.empty()) {
    int u = Q.front();
    Q.pop_front();

    if(u==n+1) {
      if(ans==-1||layer[u]<ans) ans=layer[u]; 
    }

    visited[u] = true;
    //printf("Node %d (%d,%d): Layer %d\n",u,node[u].first,node[u].second,layer[u]);
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
  int x, y;
  scanf("%d %d", &n, &r);
  for(int i=2;i<=n+1;i++) {
    scanf("%d %d",&x,&y);
    node[i] = make_pair(x,y);
  }
}
void prepare_adj() {
  for(int i=1;i<=n+1;i++) {
    for(int j=i+1;j<=n+1;j++) {
      if(i==j) continue;
      //printf("%d %d vs %d %d",node[i].first,node[i].second,node[j].first,node[j].second);
      if(pow(node[j].first-node[i].first,2)+pow(node[j].second-node[i].second,2)>r*r) {
        //printf(" -- too far\n");
        continue;
      } else {
        //printf("\n");
      }
      

      adj[i].push_back(j);
      deg[i]++;
      adj[j].push_back(i);
      deg[j]++;
    }
  }
}
int main() {
  node[1] = make_pair(0,0);
  read_input();
  node[n+1] = make_pair(100,100);
  prepare_adj();
  for(int i=1;i<=n+1;i++) {
    visited[i] = false;
  }
  bfs(1);
  printf("%d",ans);
  return 0;
}