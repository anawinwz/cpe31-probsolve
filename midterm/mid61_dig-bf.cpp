/*
TASK: mid61_dig
LANG: C++
*/
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
pair<int,int> parent[51][51];
path make_path(int i, int j, int cost) {
  path n;
  n.first = i;
  n.second = j;
  n.cost = cost;
  return n;
}
int bfs(int si, int sj, int initcost, int allow[3]) {
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
      parent[v.first][v.second] = make_pair(u.first,u.second);
      if(map[v.first][v.second]=='#') {
        continue;
      }
      bool canGo = true;
      if(map[v.first][v.second]=='*') {
        
        if(allow[0]==-1 || allow[0]!=v.first || allow[1]!=v.second) canGo = false;
        if(allow[2]==0 && v.first!=u.first) canGo = false; //same row
        if(allow[2]==1 && v.second!=u.second) canGo = false; //same col
        
      } else if(map[v.first][v.second]=='|') {
        if(v.second!=u.second) canGo = false;
      } else if(map[v.first][v.second]=='-') {
        if(v.first!=u.first) canGo = false;
      }
      
      if(!canGo) {
        if(cost[v.first][v.second]==0 || u.cost+1<cost[v.first][v.second]) 
          cost[v.first][v.second] = u.cost+1;
        continue;
      }
      Q.push_back(make_path(v.first, v.second, u.cost+1));
    }


  }
  return -1;
}
int* allow(int a,int b, int c){
  int ret[3] = {a,b,c};
  return ret;
}
int main() {
  scanf("%d %d",&r,&c);
  scanf("%d %d %d %d",&starti,&startj,&ei,&ej);
  --starti; --startj; --ei; --ej;
  for(int i=0;i<r;i++) {
    scanf("%s",&map[i]);
  }
  
  int NOTALLOW[3] = {-1,-1,-1};
  int defans = bfs(starti,startj,0, NOTALLOW); 
  
  int tmp, ans = defans;
  for(int i=1;i<r-1;i++) {
    for(int j=1;j<c-1;j++) {
      if(map[i][j]!='*') continue;
      
      tmp = -1;

      map[i][j] = '|';
      tmp = bfs(starti,startj,0,NOTALLOW);
      if(tmp!=-1 && (ans==-1 || tmp<ans)) ans = tmp;

      
      map[i][j] = '-';
      tmp = bfs(starti,startj,0,NOTALLOW);
      if(tmp!=-1 && (ans==-1 || tmp<ans)) ans = tmp;

      map[i][j] = '*';
    }
  }
  printf("%d",ans);
  return 0;  
}