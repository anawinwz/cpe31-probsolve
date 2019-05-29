#include<cstdio>
#include<set>
#include<vector>
#include<climits>
#include<utility>
#define MAXN 100001
using namespace std;
typedef pair<int, int> intpair;

vector<intpair> adj[MAXN]; 
int n, m;
long long int dijkstra(int start, int end) {
  long long int dist[MAXN];
  bool visited[MAXN] = {false};
  for(int i=1;i<=n;i++) dist[i] = INT_MAX;
  dist[start] = 0;
  set<intpair> waiting;
  waiting.insert(make_pair(0, start));

  int bestu;
  for(int i=0;i<n;i++){
    for (set<intpair>::iterator it = waiting.begin(); it != waiting.end(); ) {
      if(visited[it->second]) {
        waiting.erase(it);
        it = waiting.begin();
        continue;
      }
      bestu = it->second;
      waiting.erase(it);
      it = waiting.begin();
      break;
    }
    visited[bestu] = true;
    
    for(vector<intpair>::iterator it=adj[bestu].begin();it!=adj[bestu].end();++it) {
      if(visited[it->second]) continue;
      if(dist[bestu]+it->first < dist[it->second]) {
        dist[it->second] = dist[bestu]+it->first;
        waiting.insert(make_pair(dist[it->second], it->second));
      }
    }
  }
  return dist[end];
}
int main() {
  scanf("%d %d",&n,&m);
  
  int a,b,w;
  for(int mm=0;mm<m;mm++) {
    scanf("%d %d %d",&a,&b,&w);
    adj[a].push_back(make_pair(w,b));
    adj[b].push_back(make_pair(w,a));
  }
  printf("%lli", dijkstra(1,n));
  return 0;
}