#include<iostream>
#include<cmath>
using namespace std;
int tbl[501][501];
int main() {
  int w,h,n,left,x[2],y[2],tmp;
  while(true) {
    cin >> w >> h >> n;
    if (w==0 && h==0 && n==0) break;
    left = w*h;
    for(int i=0;i<=h;i++) for(int j=0;j<=w;j++) tbl[i][j]=0;
    for(int nn=0;nn<n;nn++) {
      cin >> x[0] >> y[0] >> x[1] >> y[1];
      if(y[1]<y[0]) {
        tmp = y[0];
        y[0] = y[1];
        y[1] = tmp;
      }
      if(x[1]<x[0]) {
        tmp = x[0];
        x[0] = x[1];
        x[1] = tmp;
      }

      for(int i=y[0];i<=y[1];i++) {
        for(int j=x[0];j<=x[1];j++) {
          tbl[i][j] = 1;
        }
      }
    }
    for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) if(tbl[i][j]==1) left--;
    /*for(int i=1;i<=h;i++) {
      for(int j=1;j<=w;j++) cout << tbl[i][j] << " ";
      cout << endl;
    }*/
    cout << "There " << ((left>1) ?"are ":"is ");
    switch(left) {
      case 0: cout << "no";break;
      case 1: cout << "one";break;
      default: cout << left;break;
    }
    cout << " empty spot" << ((left>1||left==0)?"s.":".") << endl;
  }
  return 0;
}