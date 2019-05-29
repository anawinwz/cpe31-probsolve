#include <cstdio>
#include <set>
#include <vector>
#include <climits>
#include <utility>
#define MAXN 100001
using namespace std;
typedef pair<int, int> intpair;

int N, n, m, S, T;
long long int dist[MAXN];
long long int dijkstra(int start, int end)
{
  //printf("Start: %d End: %d\n",start, end);
  
  int a, b, w;
  vector<intpair> adj[MAXN];
  for (int mm = 0; mm < m; mm++)
  {
    scanf("%d %d %d", &a, &b, &w);
    adj[a].push_back(make_pair(w, b));
    adj[b].push_back(make_pair(w, a));
  }

  bool visited[MAXN];
  for (int i = 0; i <= n; i++) dist[i] = INT_MAX, visited[i] = false;
  dist[start] = 0;
  set<intpair> waiting;
  waiting.insert(make_pair(0, start));
  
  int bestu;
  for (int i = 0; i < n; i++)
  {
    for (set<intpair>::iterator it = waiting.begin(); it != waiting.end(); ) {
      if(visited[it->second]) {
        //printf("\talready visited candidate: %d!\n",it->second);
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
    //printf("\tnow: %d, dist: %d\n",bestu,dist[bestu]);

    for (vector<intpair>::iterator it = adj[bestu].begin(); it != adj[bestu].end(); ++it)
    {
      if (visited[it->second])
        continue;
      //printf("\t\t(%d,%d) -> %d\n",bestu,it->second,it->first);
      //printf("\t\t%lli + %d < %lli\n", dist[bestu],it->first, dist[it->second]);
      if (dist[bestu] + it->first < dist[it->second])
      {
        dist[it->second] = dist[bestu] + it->first;
        //printf("\t\t^ pick this for %d, now %lli!\n",it->second,dist[it->second]);
        waiting.insert(make_pair(dist[it->second], it->second));
      }
    }
  }
  //printf("---end---\n");
  return dist[end];
}
int main()
{
  long long int ans;
  scanf("%d", &N);
  for (int NN = 1; NN <= N; NN++)
  {
    scanf("%d %d %d %d", &n, &m, &S, &T);
    ans = dijkstra(S, T);
    if (ans == INT_MAX)
      printf("Case #%d: unreachable\n", NN);
    else
      printf("Case #%d: %lli\n", NN, ans);
  }

  return 0;
}