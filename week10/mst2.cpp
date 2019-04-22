#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
struct Edge {
  int v1;
  int v2;
  int cost;
  Edge(int v1, int v2, int cost)
    : v1(v1), v2(v2), cost(cost) {}
};
set<Edge> e;
inline bool operator<(const Edge& lhs, const Edge& rhs)
{
  return lhs.cost < rhs.cost;
}
bool sortme(Edge a, Edge b) {
  return a.cost < b.cost;
}
int sortme2(const void* p1, const void* p2) {
  return ((Edge*)p1)->cost - ((Edge*)p2)->cost;
}
int n, m;
int parent[100001], rnk[100001]; 
int find(int i) {
  if(parent[i]==0) {
    return i;
  } else {
    return find(parent[i]); 
  }
}
bool uni(int x,int y) {
  int a = find(x);
  int b = find(y);
  if(a==b) return false;

  if(rnk[a]<rnk[b]) {
    parent[a] = b;
  } else if(rnk[a]>rnk[b]) {
    parent[b] = a;
  } else {
    parent[a] = b;
    rnk[b]++;
  }
  return true;
}
int ans=0;
int main() {
  scanf("%d %d",&n,&m);
  int v1,v2,cost;
  for(int mm=0;mm<m;mm++) {
    scanf("%d %d %d",&v1,&v2,&cost);
    e.insert(Edge(v1, v2, cost));
  }
  //sort(e.begin(),e.end(),sortme);
  set<Edge>::iterator it;
  long long int totalCost = 0;
  while(ans<n-1) {
    it = e.begin();
    if(uni(it->v1,it->v2)) {
      totalCost += (*it).cost;
      ans++;
      //printf("\tSelect %d %d, %d\n",it->v1,it->v2,it->cost);
    }
    e.erase(it);
  }
  printf("%lli",totalCost);
}