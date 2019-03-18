#include<stdio.h>
#include<cmath>
#include<cstdlib>
int n = 4, tick = 0;
int w[5]={0,7,3,2,1};
int meter(int i) {
  if(tick>log2(n)) {
    printf("Failed!");
    exit(0);
  }
  tick++;
  int sum = 0;
  for(int k=i;i<=n;i++) {
    sum+=w[i];
  }
  return sum;
}
int main(){
  int lo=n, hi=1, mid, W = meter(1);
  while(true) {
    mid = floor((lo+hi)/2);
    printf("%d << %d >> %d\n",lo,mid,hi);
    if(lo==mid) {
      printf("found %d\n",lo);
      break;
    }
    int tmp = meter(mid);
    if(tmp>W-tmp) {
      hi = mid;
    } else {
      lo = mid+1;
    }
  }

}