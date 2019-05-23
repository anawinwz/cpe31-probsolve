#include<cstdio>

#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
/*--- START MST RELATED ---*/
struct Edge {
  int v1;
  int v2;
  int cost;
  Edge(int v1, int v2, int cost)
    : v1(v1), v2(v2), cost(cost) {}
};
vector<Edge> e;
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
/*--- STOP MST RELATED ---*/
int d[100001]; //Dist per sec
int main() {
  scanf("%d",&n);//Chemicals
  scanf("%d",&m);//Edges
  for(int nn=0;nn<n;nn++) {
    scanf("%d",&d[nn]);
  }
  int v1,v2,cost;
  for(int mm=0;mm<m;mm++) {
    scanf("%d %d %d",&v1,&v2,&cost);
    e.push_back(Edge(v1-1, v2-1, ceil((double)cost/(d[v1-1]+d[v2-1]))));
  }
  sort(e.begin(),e.end(),sortme);
  long long int minSec = 0;
  int ans=0;
  for(vector<Edge>::iterator it=e.begin();it!=e.end();++it){
    if(uni(it->v1,it->v2)) {
      if(it->cost>minSec) minSec = it->cost;
      ans++;
      //printf("\tSelect %d %d, %d\n",it->v1,it->v2,it->cost);
      if(ans==n-1) break;
    }
  }
  printf("%lli",minSec);
}