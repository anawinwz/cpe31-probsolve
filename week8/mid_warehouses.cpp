#include<cstdio>
#include<list>
#include<vector>
#define MAXN 100000
using namespace std;
vector<int> adj[MAXN+1];
int n, m, k;
bool bfs(int start, int end) {
  bool visited[MAXN+1] = {false};
  list<int> Q;
  Q.push_back(start);
  while(!Q.empty()) {
    int now = Q.front();
    Q.pop_front();

    visited[now] = true;
    if(now==end) {
      return true;
    }

    for(int i=0;i<adj[now].size();i++) {
      if(visited[adj[now][i]]) continue;
      Q.push_back(adj[now][i]);
    }
  }
  return false;
}
int main() {
  scanf("%d %d %d",&n,&m,&k);
  int x,y;
  for(int mm=0;mm<m;mm++){
    scanf("%d %d",&x,&y);
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  for(int kk=0;kk<k;kk++){
    scanf("%d %d",&x,&y);
    if(bfs(x,y)) printf("1");
    else printf("0");
    printf("\n");
  }
}