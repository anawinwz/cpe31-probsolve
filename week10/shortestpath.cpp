#include<cstdio>
#include<set>
#include<vector>
#include<climits>
#include<utility>
#include<algorithm>
#define MAXN 100001
using namespace std;
long long int dist[MAXN];
//bool visited[MAXN];
set<pair<int, int> > adj[MAXN];
vector<int> vertex; 
int n, m, visitCnt = 0;
bool sortme(int a, int b) {
  return dist[a] < dist[b];
}
void dijkstra() {
  int bestu;
  while(visitCnt < n) {
    sort(vertex.begin(),vertex.end(),sortme);
    bestu = vertex.front();
    vertex.erase(vertex.begin());
    visitCnt++;
    for(set<pair<int, int> >::iterator it=adj[bestu].begin();it!=adj[bestu].end();++it) {
      if(dist[bestu]+it->first < dist[it->second]) {
        dist[it->second] = dist[bestu]+it->first;
      }
    }
  }
}
int main() {
  scanf("%d %d",&n,&m);
  for(int i=1;i<=n;i++) dist[i] = INT_MAX, vertex.push_back(i);
  int a,b,w;
  dist[1] = 0;
  for(int mm=0;mm<m;mm++) {
    scanf("%d %d %d",&a,&b,&w);
    adj[a].insert(make_pair(w,b));
    adj[b].insert(make_pair(w,a));
  }
  dijkstra();
  printf("%lli",dist[n]);
  return 0;
}