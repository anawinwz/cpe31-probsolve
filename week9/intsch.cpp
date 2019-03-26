#include<cstdio>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;
struct job {
  int s;
  int t;
};
int n;
job j[100000];
vector<int> J;
vector<int> A;
bool sortme(job a, job b){
  return a.t<b.t || (a.t==b.t && a.t >= b.s);
}
bool sortjob(int a,int b){
  return sortme(j[a],j[b]);
}
int main() {
  scanf("%d",&n);
  for(int i=0;i<n;i++) {
    scanf("%d %d",&j[i].s,&j[i].t);
    J.push_back(i);
  }
  sort(J.begin(),J.end(),sortjob);
  int ans=0, lastend=0;
  for(int i=0;i<J.size();i++) {
    if(i!=0 && j[J[i]].s<lastend) continue;
    ans++;
    lastend = j[J[i]].t; 
  }
  printf("%d",ans); 
  return 0;
}