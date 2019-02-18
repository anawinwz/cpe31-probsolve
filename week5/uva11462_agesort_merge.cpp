#include<iostream>
#include<cmath>
using namespace std;
#define MAXN 2000000
int a[MAXN+1];
int* merge(int a[], int an, int b[], int bn) {
  int ai=0, bi=0, resi=0;
  int *res = new int[an+bn];
  while(ai<an) {
    if(bi>=bn || a[ai]<=b[bi]) {
      res[resi++]=a[ai++];
    } else {
      res[resi++]=b[bi++];
    }
  }
  while(bi<bn) {
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
  ios::sync_with_stdio(false);

  int n;
  int *ans;
  while(true) {
    cin >> n;
    if(n==0) break;
    for(int i=0;i<n;i++) {
      cin >> a[i];
    }
    ans = merge_sort(a,n);
    for(int i=0;i<n;i++) {
      cout << ans[i];
      if(i+1<n) cout << " ";
    }
    cout << "\n";
  }
  return 0;
}