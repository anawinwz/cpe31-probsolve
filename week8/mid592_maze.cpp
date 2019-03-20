#include<cstdio>
#include<utility>
#include<list>
#include<vector>
#define MAXN 20
using namespace std;
char map[MAXN+1][MAXN+1];
int n, q;
bool bfs(int si, int sj, int ei, int ej) {
  list< pair<pair<int,int>,int > > Q;
  Q.push_back(make_pair(make_pair(si,sj),0)); 
  pair<pair<int,int>,int > front; 
  pair<int,int> u;
  bool visited[MAXN+1][MAXN+1] = {{false}};
  while(!Q.empty()) {
    front = Q.front();
    Q.pop_front();
    u = front.first;
    if(visited[u.first][u.second]) continue;
    //printf("%d %d\n",u.first,u.second);

    visited[u.first][u.second] = true;
    if(u.first==ei && u.second==ej) return true;
    
    vector< pair<int,int> > adj;
    if(u.first+1<n) adj.push_back(make_pair(u.first+1,u.second));
    if(u.first-1>=0) adj.push_back(make_pair(u.first-1,u.second));
    if(u.second+1<n) adj.push_back(make_pair(u.first,u.second+1));
    if(u.second-1>=0) adj.push_back(make_pair(u.first,u.second-1));

    int key=0;
    for(int i=0;i<adj.size();i++) {
      if(visited[adj[i].first][adj[i].second] || map[adj[i].first][adj[i].second]=='#') continue;
      if(map[adj[i].first][adj[i].second]=='O') {
        if(front.second==1) continue;
        //printf("[%d %d] %d %d try to use key at %d %d\n",si,sj,u.first,u.second,adj[i].first,adj[i].second);
        key = 1;
      } else {
        key = front.second;
      }
      Q.push_back(make_pair(adj[i],key));
    }
  }
  return false;
} 
int main() {
  scanf("%d %d",&n,&q);
  for(int i=0;i<n;i++) {
    scanf("%s",&map[i]);
  } 
  int x1,y1,x2,y2;
  for(int qq=0;qq<q;qq++) {
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    printf("%s\n",((bfs(x1-1,y1-1,x2-1,y2-1))?"yes":"no")); 
  }  
  return 0; 
}