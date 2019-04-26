#include<cstdio>
#include<set>
#include<vector>
#include<climits>
#include<utility>
#define MAXN 100001
using namespace std;
typedef pair<int, int> intpair;
long long int dist[MAXN];
bool visited[MAXN];
set<intpair> waiting;
vector<intpair> adj[MAXN]; 
int n, m, visitCnt = 0;
void dijkstra() {
  int bestu;
  for(int i=0;i<n;i++){
    bestu = waiting.begin()->second;
    waiting.erase(waiting.begin());
    
    for(vector<intpair>::iterator it=adj[bestu].begin();it!=adj[bestu].end();++it) {
      if(visited[bestu]) continue;
      if(dist[bestu]+it->first < dist[it->second]) {
        dist[it->second] = dist[bestu]+it->first;
        waiting.insert(make_pair(dist[it->second], it->second));
      }
    }
    visited[bestu] = true;
  }
}
int main() {
  scanf("%d %d",&n,&m);
  for(int i=1;i<=n;i++) dist[i] = INT_MAX;
  int a,b,w;
  dist[1] = 0;
  for(int mm=0;mm<m;mm++) {
    scanf("%d %d %d",&a,&b,&w);
    adj[a].push_back(make_pair(w,b));
    adj[b].push_back(make_pair(w,a));
  }
  waiting.insert(make_pair(0, 1));
  dijkstra();
  printf("%lli",dist[n]);
  return 0;
}