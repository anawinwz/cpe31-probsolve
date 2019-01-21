#include<iostream>
using namespace std;
int maxOp(int a, int b) {
  if (a>b) return 0;
  else return 1;
}
int main(){
  char op[2][302], res[306];
  cin >> op[0];
  cin >> op[1];

  int n[2], resI=0;
  for (n[0]=0;op[0][n[0]]!='\0';n[0]++) {}
  for (n[1]=0;op[1][n[1]]!='\0';n[1]++) {}

  //cout << "n[0] : " << n[0] << endl;
  //cout << "n[1] : " << n[1] << endl;

  int mainOp = (n[0]>n[1]) ? 0:1,
      subOp = (mainOp==1) ? 0:1,
      opDiff = n[mainOp]-n[subOp],
      now, carry=0;
  for (int i=n[mainOp]-1;i>=0;i--) {
    //cout << "----------- i: " << i << endl;
    now = op[mainOp][i] - '0';
    //cout << "Op1: " << op[mainOp][i] << endl;
    if (n[mainOp]-i <= n[subOp]) {
      now += op[subOp][i-opDiff] - '0';
      //cout << "Op2: " << op[subOp][i-opDiff] << endl;
    }
    now += carry;
    if (now > 9) {
      carry = now/10;
      now %= 10;
    } else {
      carry = 0;
    }
    res[resI++] = now + '0';
  }
  if(carry > 0) res[resI++] = carry + '0';
  for(int i=resI-1;i>=0;i--) cout << res[i];
}