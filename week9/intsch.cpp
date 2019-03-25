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
  int ans=0, jend;
  while(!J.empty()){
    jend = j[J[0]].t;
    A.push_back(jend);
    J.erase(J.begin());

    for(vector<int>::iterator it=J.begin();it!=J.end();){
      if(j[*it].s<jend) {
        //printf("\tDelete job (%d,%d)\n",j[*it].s,j[*it].t);
        it = J.erase(it);
      }
      else ++it;
    }
    ans++;
  }
  printf("%d",ans); 
  return 0;
}