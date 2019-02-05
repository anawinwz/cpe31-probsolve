#include<iostream>
#include<cmath>
using namespace std;
int main() {
  int n, x, y;
  cin >> n;
  for(int i=0;i<n;i++) {
    cin >> x >> y;
    cout << (int)ceil(x/3)*(int)ceil(y/3) << endl;
  }
  return 0;
}