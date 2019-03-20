#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int n, m, now=0, target=0;
struct droid{
  int idx;
  int pos;
};
droid dr[100001];
bool sortme(droid a, droid b) {
  return (abs(target-a.pos) < abs(target-b.pos)) || (abs(target-a.pos)==abs(target-b.pos) && a.pos<b.pos);
} 
int main() {
  scanf("%d %d",&n,&m);
  for(int i=0;i<n;i++){
    scanf("%d",&dr[i].pos);
    dr[i].idx = i;
  }
  int ans=0;
  for(int mm=0;mm<m;mm++) {
    scanf("%d",&target);
    sort(dr,dr+n,sortme);
    for(int i=0;i<n;i++) {
      if(dr[i].pos!=now) {
        ans+=abs(target-dr[i].pos);
        now=dr[i].pos;
        break;
      }
    }
  }
  printf("%d",ans);
  return 0;
}