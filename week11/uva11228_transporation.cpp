#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#include<utility>
using namespace std;
struct Edge {
  int v1;
  int v2;
  double cost;
  Edge(int v1, int v2, double cost)
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
int n, m, r, states;
double roads, rails;
int parent[1001], rnk[1001]; 
pair<int,int > node[1001]; 
int find(int i) {
  if(parent[i]==-1) {
    return i;
  } else {
    return find(parent[i]); 
  }
}
void reset() {
  for(int i=0;i<=n;i++) parent[i]=-1,rnk[i]=0;
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

double dist(int a, int b) {
  return sqrt(pow(node[b].first-node[a].first,2)+pow(node[b].second-node[a].second,2));
}

int main() {
  int t;
  scanf("%d",&t);
  for(int tt=0;tt<t;tt++) {
    scanf("%d %d",&n,&r);
    int x,y;
    for(int nn=0;nn<n;nn++) {
      scanf("%d %d",&x,&y);
      node[nn].first = x;
      node[nn].second = y;
    }

    reset();
    e.clear();
    int ans=0;
    double cost;
    states = roads = rails = 0;
    for(int v1=0;v1<n;v1++) {
      for(int v2=0;v2<n;v2++) {
        if(v1==v2) continue;
        cost = dist(v1,v2);
        e.push_back(Edge(v1, v2, cost));
      }
    }
    sort(e.begin(),e.end(),sortme);
    
    for(vector<Edge>::iterator it=e.begin();it!=e.end();++it){
      if(uni(it->v1,it->v2)) {
        if(it->cost<=r) roads += it->cost;
        else rails += it->cost, states++;
        ans++;
        if(ans==n-1) break;
      } 
    }
    printf("Case #%d: %d %d %d\n",tt+1,states+1,(int)round(roads),(int)round(rails));
  }
}