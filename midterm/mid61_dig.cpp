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
      parent[v.first][v.second] = make_pair(u.first,u.second);
      if(map[v.first][v.second]!='.') {
        if(map[v.first][v.second]=='*') {
          if(cost[v.first][v.second]==0 || u.cost+1<cost[v.first][v.second]) 
            cost[v.first][v.second] = u.cost+1;
        }
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
  
  int defans = bfs(starti,startj,0); 
  
  int tmp, ans = defans;
  for(int i=1;i<r-1;i++) {
    for(int j=1;j<c-1;j++) {
      if(map[i][j]!='*' || cost[i][j]==0) continue;
      
      tmp = -1;
      //printf("* %d %d (cost %d)\n",i+1,j+1,cost[i][j]);
      if(parent[i][j].first==i) {
        //printf("try as same row\n");
        if(parent[i][j].second==j-1) tmp = bfs(i,j+1,cost[i][j]+1);
        else tmp = bfs(i,j-1,cost[i][j]+1);
      } else {
        //printf("try as same col\n");
        if(parent[i][j].second==i-1) tmp = bfs(i+1,j,cost[i][j]+1);
        else tmp = bfs(i-1,j,cost[i][j]+1);
      }
      //printf("tryres = %d, nowans = %d\n",tmp,ans);
      if(tmp!=-1 && (ans==-1 || tmp<ans)) ans = tmp;
    }
  }
  printf("%d",ans);
  return 0;  
}