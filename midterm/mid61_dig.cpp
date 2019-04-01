#include<cstdio>
#include<utility>
#include<list>
#include<vector>
using namespace std;
struct path{
  int first;
  int second;
  int cost;
};
int starti, startj, ei, ej, c, r;
int dp[51][51], cost[51][51];
char map[51][51];
path make_path(int i, int j, int cost) {
  path n;
  n.first = i;
  n.second = j;
  n.cost = cost;
  return n;
}
int bfs(int si, int sj, int initcost) {
  bool visited[51][51] = {{false}};
  list< path > Q;
  Q.push_back(make_path(si,sj,initcost));
  path u;
  pair<int,int> v;
  vector< pair<int,int> > adj;
  while(!Q.empty()) {
    u = Q.front();
    Q.pop_front();
    if(visited[u.first][u.second]) continue;

    visited[u.first][u.second] = true;
    if(cost[u.first][u.second]==0 || u.cost < cost[u.first][u.second])
      cost[u.first][u.second] = u.cost;
    //printf("%d %d\n",u.first,u.second);
    if(u.first==ei && u.second==ej) {
      //Found
      return u.cost;
    }

    adj.push_back(make_pair(u.first-1,u.second));
    adj.push_back(make_pair(u.first+1,u.second));
    adj.push_back(make_pair(u.first,u.second-1));
    adj.push_back(make_pair(u.first,u.second+1));

    for(int i=0;i<adj.size();i++) {
      v = adj[i];
      if(v.first<0 || v.first >= r || v.second < 0 || v.second >= c) continue;
      if(map[v.first][v.second]!='.') {
        if(map[v.first][v.second]=='*') cost[v.first][v.second] = u.cost+1;
        continue;
      }
      
      Q.push_back(make_path(v.first, v.second, u.cost+1));
    }


  }
  return -1;
}

int main() {
  scanf("%d %d",&r,&c);
  scanf("%d %d %d %d",&starti,&startj,&ei,&ej);
  --starti; --startj; --ei; --ej;
  for(int i=0;i<r;i++) {
    scanf("%s",&map[i]);
  }
  printf("%d",bfs(starti,startj, 0));
  return 0;  
}