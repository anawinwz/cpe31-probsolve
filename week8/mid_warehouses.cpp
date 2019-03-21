#include<cstdio>
#include<list>
#include<vector>
#include<set>
#include<iterator>
#define MAXN 100000
using namespace std;
bool visited[MAXN+1] = {false};
vector<int> adj[MAXN+1];
set<int> cango[MAXN+1];
int n, m, k;
void bfs(int start) {
  bool isFound = false;

  list<vector<int> > Q;
  int now;
  vector<int> a;
  a.push_back(start);
  Q.push_back(a); 
  while(!Q.empty()) {
    a = Q.front();
    now = a.back();
    Q.pop_front();
    if(visited[now]) continue;
    visited[now] = true;
    copy(a.begin(),a.end(),inserter(cango[start],cango[start].end()));
    copy(a.begin(),a.end(),inserter(cango[now],cango[now].end()));
    for(int i=0;i<adj[now].size();i++) {
      if(visited[adj[now][i]]) continue;
      vector<int> newvec = a;
      newvec.push_back(adj[now][i]);
      Q.push_back(newvec);
    } 
  }
  
  return;
}
int main() {
  scanf("%d %d %d",&n,&m,&k);
  int x,y,minn=0,maxn=0;
  for(int mm=0;mm<m;mm++){
    scanf("%d %d",&x,&y);
    if(minn==0||x<minn) minn = x;
    if(y<minn) minn = y;

    if(x>maxn) maxn = x;
    if(y>maxn) maxn = y; 

    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  for(int i=minn;i<=maxn;i++){
    bfs(i);
  }

  for(int kk=0;kk<k;kk++){
    scanf("%d %d",&x,&y);
    if(cango[x].count(y) || cango[y].count(x)) printf("1");
    else printf("0");
    printf("\n");
  }

}