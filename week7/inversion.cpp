#include<cstdio>
#include<cmath>
int a[100001];
int n;
long long ans = 0;
int* merge(int a[], int an, int b[], int bn) {
  int ai=0, bi=0, resi=0;
  int *res = new int[an+bn];
  while(ai<an) {
    if(bi>=bn || a[ai]<=b[bi]) {
      res[resi++]=a[ai++];
    } else {
      ans++;
      res[resi++]=b[bi++];
    }
  }
  while(bi<bn) {
    //ans++;
    res[resi++]=b[bi++];
  }
  return res;
}
int* merge_sort(int a[], int an) {
  if(an==1) return a;
  int split = ceil(an/2);
  return merge(merge_sort(a,split),split,merge_sort(a+split,an-split),an-split);
}

int main() {
  scanf("%d",&n);
  for(int i=0;i<n;i++) scanf("%d",&a[i]);
  merge_sort(a,n);
  printf("%lli",ans);
  return 0;
}