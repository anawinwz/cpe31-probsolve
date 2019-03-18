#include<iostream>
using namespace std;
int stats[101];
int main() {
  int lvl, vid;
  cin >> lvl >> vid;

  int l,t;
  for(int i=0;i<vid;i++) {
    cin >> l >> t;
    if(stats[l]==0 || t<stats[l]) stats[l]=t;
  }
  int sum = 0;
  for(int i=1;i<=lvl;i++) sum+=stats[i];
  cout << sum << "\n";
  for(int i=1;i<=lvl;i++) {
    cout << i << " " << stats[i] << "\n";
  }
  return 0;
}