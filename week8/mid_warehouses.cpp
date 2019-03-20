#include<cstdio>
#include<list>
#include<vector>
#include<map>
#include<utility>
#define MAXN 100000
using namespace std;
vector<int> adj[MAXN+1]; 
map<pair<int,int>,int> dp;
map<int, int> direct;
int n, m, k;
bool bfs(int start, int end) {
  if(dp.count(make_pair(start,end))>0) {
    switch(dp[make_pair(start,end)]) {
      case 1: return false;break; 
      case 2: return true;break;
    }
  }

  bool visited[MAXN+1] = {false};
  int parent[MAXN+1] = {0};
  bool isFound = false;

  list<int> Q;
  int now;
  Q.push_back(start);
  parent[start] = 0; 
  while(!Q.empty()) {
    now = Q.front();
    Q.pop_front();

    visited[now] = true;
    if(now==end || (dp.count(make_pair(now,end))>0 && dp[make_pair(now,end)]==2)) {
      dp[make_pair(start,end)] = 2;
      isFound = true;
      break;
    }

    for(int i=0;i<adj[now].size();i++) {
      if(visited[adj[now][i]]) continue;
      parent[adj[now][i]] = now;
      Q.push_back(adj[now][i]);
    }
  }
  if(isFound) {
    while(now!=0) {
      dp[make_pair(now,end)] = 2;
      now = parent[now];
    }
  } else {
    dp[make_pair(start,end)] = 1;
  }
  return isFound;
}
int main() {
  scanf("%d %d %d",&n,&m,&k);
  int x,y;
  for(int mm=0;mm<m;mm++){
    scanf("%d %d",&x,&y);
    adj[x].push_back(y);
    adj[y].push_back(x);
    dp[make_pair(x,y)] = 2;
    dp[make_pair(y,x)] = 2;
  }
  for(int kk=0;kk<k;kk++){
    scanf("%d %d",&x,&y);
    if(dp.count(make_pair(x,y)) && dp[make_pair(x,y)]>0) printf("%d",dp[make_pair(x,y)]-1);
    else if(adj[y].size()>0 && adj[x].size()>0 && bfs(x,y)) printf("1");
    else printf("0");
    printf("\n");
  }
}