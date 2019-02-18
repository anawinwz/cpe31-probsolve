#include<cstdio>
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
int seq[1000001];
int endi;
vector<int> primes;
int nod(int n) {
  int ans=0;
  for(int i=1;i<=sqrt(n);i++) {
    if(n%i!=0) continue;
    if(n/i==i) ans++;
    else ans+=2;
  }
  return ans;
}
int bsearch(int lo, int hi, int find) {
  //cout << "--------bsearch("<<lo<<","<<hi<<","<<find<<")------------"<<endl;
  int mid;
  while(lo!=hi) {
    mid = (lo+hi)/2;
    //printf("%d(%d) - %d(%d) - %d(%d)\n", seq[lo],lo,seq[mid],mid,seq[hi],hi); 
    if(find==seq[mid]) {
      return mid;
    } else if(find<seq[mid]) {
      //go left
      hi = mid;
    } else if(mid+1<=endi && find >= seq[mid+1]) {
      lo = mid+1;
    } else {
      break;
    }
  }
  return mid;
}
int main() {
  ios::sync_with_stdio(false);
  seq[0] = 1;
  for(endi=1;endi<=100000;endi++) {
    seq[endi] = seq[endi-1] + nod(seq[endi-1]);
    //cout << seq[i] << "\n";
    if(seq[endi]>1000000) break;
  }
  
  int t, a, b, tmpa, tmpb, ans;
  cin >> t;
  for(int tt=0;tt<t;tt++) {
    cin >> a >> b;
    tmpa = bsearch(0,endi,a);
    tmpb = bsearch(0,endi,b);
    cout << "Case " << tt+1 <<": ";
    if(tmpa>0|| tmpb>0 || seq[tmpa]>=a) {
      ans = tmpb-tmpa;
      if(seq[tmpa]<a) ans--;
      if(seq[tmpb]<=b) ans++;
      cout << ans; 
    } else {
      cout << 0;
    }
    cout << endl;
  }

  return 0;
}