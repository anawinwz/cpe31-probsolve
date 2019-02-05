#include<iostream>
using namespace std;
int countans(int n, int m,char tbl[101][101]) {
  int ans = 0;
  for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
      if(tbl[i][j]=='0') continue;
      ans++;
      if(j+1<m && tbl[i][j+1]=='1') ans++;
      if(i+1<n && tbl[i+1][j]=='1') ans++; 
    }
  }
  return ans;
}
int main(){
  int n,m;
  char tbl[101][101];
  while (true) {
    cin >> n;
    if (n==0) break;
    cin >> m;
    for(int i=0;i<n;i++) cin >> tbl[i];
    cout << countans(n,m,tbl) << endl;
  }
  return 0;
}