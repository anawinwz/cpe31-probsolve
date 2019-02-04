#include<iostream>
using namespace std;
int cycle(int n) {
  if (n==1) return 1;
  return 1 + cycle((n%2==1)?3*n+1:n/2);
}
int main() {
  int maxx, tmp, x, y;
  while (cin >> x >> y) {
    cout << x << " " << y << " ";
    maxx = 0;
    if (x > y) {
      tmp = x;
      x = y;
      y = tmp;
    }
    for(int i=x;i<=y;i++){
      tmp = cycle(i);
      if(tmp>maxx) maxx = tmp;
    }
    cout << maxx << endl;
  }
  return 0;
}