#include<cstdio>
#include<set>
#include<climits>
#include<utility>
#define MAXN 100001
using namespace std;
long long int dist[MAXN];
bool visited[MAXN];
set<pair<int, int> > adj[MAXN]; 
int n, m;
long long int ans=0;
void go(int now) {
  //printf("now: %d, dist[now]: %lli\n",now,dist[now]);
  visited[now] = true;
  for(set<pair<int,int> >::iterator it=adj[now].begin();it!=adj[now].end();++it) {
    //printf("\t(%d,%d)\n",it->first,it->second);
    if(visited[it->second]) continue;
    if(dist[now]+it->first<dist[it->second]) {
      dist[it->second] = dist[now]+it->first;
      //printf("\tcan go to %d with shorter dist (%lli)\n",it->first,dist[it->second]);
    }
    go(it->second);
  }
}
int main() {
  scanf("%d %d",&n,&m);
  for(int i=0;i<=n;i++) dist[i] = INT_MAX;
  int a,b,w;
  dist[1] = 0;
  for(int mm=0;mm<m;mm++) {
    scanf("%d %d %d",&a,&b,&w);
    adj[a].insert(make_pair(w,b));
    adj[b].insert(make_pair(w,a));
  }
  go(1);
  printf("%lli",dist[n]);
  return 0;
}