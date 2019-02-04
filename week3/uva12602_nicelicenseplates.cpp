#include<iostream>
#include<cmath>
using namespace std;
int main() {
  int n;
  cin >> n;
  char alpha[5];
  int digit;
  int alphaSum;
  for(int i=0;i<n;i++) {
    cin >> alpha[0] >> alpha[1] >> alpha[2] >> alpha[3];
    alpha[4]='\0';
    cin >> digit;
    
    alphaSum = 0;
    for(int j=0;j<3;j++) alphaSum += (alpha[j]-'A') * pow(26,2-j);
    if(abs(alphaSum-digit)<=100) cout << "nice";
    else cout << "not nice";
    cout << endl;
  }

  return 0;
}