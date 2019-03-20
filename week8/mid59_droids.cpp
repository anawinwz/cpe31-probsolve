#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int n, m, now=0;
vector<int> dr;

int main() {
  scanf("%d %d",&n,&m);
  int inp;
  for(int i=0;i<n;i++){
    scanf("%d",&inp);
    dr.push_back(inp);
  }
  sort(dr.begin(),dr.end());
  int ans=0, target;
  vector<int>::iterator res;
  for(int mm=0;mm<m;mm++) {
    scanf("%d",&target);

    if(target>dr[n-1]) {
      res = dr.begin()+n-1;
      if(*res==now) {
        res--;
      }
    } else {
      res = --upper_bound(dr.begin(),dr.end(),target);
      if(*res==now) {
        res = --upper_bound(res+1,dr.end(),target);
      }
    }
    ans+=abs(target-(*res));
    //printf("use %d for %d\n",*res,target);
    now = *res;
  }
  printf("%d",ans);
  return 0;
}