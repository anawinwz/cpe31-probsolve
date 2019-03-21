#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int n, m, now=0;
int dr[100001], drI=0;
int bsearch(int find) {
  int lo=0,hi=n-1,mid;
  while(true) {
    mid=(lo+hi)/2;
    //printf("%d %d %d\n",dr[lo],dr[mid],dr[hi]);
    if(lo==mid && mid==hi) {
      return mid;
    }
    if(dr[mid]<=find && (mid+1>=n || find<dr[mid+1])) {
      //printf("%d<%d && %d<%d",dr[mid],find,find,dr[mid+1]);
      return mid;
    }
    
    if(find==dr[mid]) {
      return mid;
    } else if(find<dr[mid]) {
      hi=mid;
    } else if(find>dr[mid]) {
      lo=mid+1;
    }
  }
}
int main() {
  scanf("%d %d",&n,&m);
  int inp;
  for(int i=0;i<n;i++){
    scanf("%d",&inp);
    dr[drI++] = inp;
  }
  sort(dr,dr+n); 
  int target, i, tmp;
  long long int ans = 0;
  for(int mm=0;mm<m;mm++) {
    scanf("%d",&target);
    i = bsearch(target);
    if(i+1<n && abs(target-dr[i+1])<abs(target-dr[i])) i++;

    if(now!=dr[i]) {
      ans += abs(target-dr[i]);
      now = dr[i];
      //printf("use %d for %d\n",dr[i],target);
    }else {
      if(i+1<n) tmp = i+1;
      if(i+1>=n || (i-1>=0 && abs(target-dr[i-1])<abs(target-dr[tmp]) ) ) tmp = i-1;
      ans += abs(target-dr[tmp]);
      now = dr[tmp];
      //printf("(Busy)use %d for %d\n",dr[tmp],target);
    }
  }
  printf("%lli",ans);
  return 0;
}