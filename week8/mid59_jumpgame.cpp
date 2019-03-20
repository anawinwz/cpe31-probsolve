#include<cstdio>
#include<utility>
#include<list>
#include<vector>
#define MAXN 20
using namespace std;
int map[MAXN+1][MAXN+1];
int n, k;
bool bfs() {
  list< pair<int,int> > Q;
  Q.push_back(make_pair(0,0));
  pair<int,int> u; int now;
  vector< pair<int,int> > adj;
  bool visited[MAXN+1][MAXN+1] = {{false}};
  while(!Q.empty()) {
    u = Q.front();
    Q.pop_front();
    if(visited[u.first][u.second]) continue;
    //printf("%d %d\n",u.first,u.second);

    visited[u.first][u.second] = true;
    if(u.first==n-1 && u.second==n-1) return true;
    
    if(u.first+1<n && map[u.first+1][u.second]<=map[u.first][u.second]+k) adj.push_back(make_pair(u.first+1,u.second));
    if(u.first-1>=0 && map[u.first-1][u.second]<=map[u.first][u.second]+k) adj.push_back(make_pair(u.first-1,u.second));
    if(u.second+1<n && map[u.first][u.second+1]<=map[u.first][u.second]+k) adj.push_back(make_pair(u.first,u.second+1));
    if(u.second-1>=0 && map[u.first][u.second-1]<=map[u.first][u.second]+k) adj.push_back(make_pair(u.first,u.second-1));

    for(int i=0;i<adj.size();i++) {
      if(visited[adj[i].first][adj[i].second]) continue;
      Q.push_back(adj[i]);
    }
  }
  return false;
} 
int main() {
  scanf("%d %d",&n,&k);
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      scanf("%d",&map[i][j]);
    }
  } 
  printf("%s",(bfs())?"yes":"no");
  return 0;
}