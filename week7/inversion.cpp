#include<cstdio>
#include<cmath>
//#define debug
int a[100001];
int n;
long long ans = 0;
int* merge(int a[], int an, int b[], int bn) {
  int ai=0, bi=0, resi=0;
  int *res = new int[an+bn];
  while(ai<an) {
    if(bi<bn && a[ai]>b[bi]) {
      ans++;
      res[resi++]=b[bi++];
    } else  {
      res[resi++]=a[ai++];
    } 
  }
  #ifdef debug
  printf("\tbi: %d\n",bi);
  #endif
  while(bi<bn) {
    ans++;
    res[resi++]=b[bi++];
  }
  return res;
}
int* merge_sort(int a[], int an) {
  if(an==1) return a;
  int split = ceil(an/2);
  return merge(merge_sort(a,split),split,merge_sort(a+split,an-split),an-split);
}
#ifdef debug
long long bruteforce(){
  long long ans = 0;
  for(int i=0;i<n;i++) {
    for(int j=i+1;j<n;j++) {
      if(a[i]>a[j]) ans++;
    }
  }
  return ans;
}
#endif
int main() {
  scanf("%d",&n);
  for(int i=0;i<n;i++) scanf("%d",&a[i]);
  int* test = merge_sort(a,n);
  printf("%lli",ans);
  #ifdef debug
  printf("\n");
  for(int i=0;i<n;i++) printf("%d ",test[i]);
  printf("\n");
  printf("\nBrute force: %lli",bruteforce());
  #endif
  return 0;
}