#include<iostream>
#include<map>
using namespace std;
int findAns(int n) {
  //cout << "findAns(" <<n << ")"<<endl;
  int state[100], on=n, j, tick=0;
  for(int m=1;m<=n*4;m++){
    //cout<<"m: "<<m<<endl;
    on=n; j=0; tick=0;
    for(int i=0;i<n;i++) state[i]=0;
    while(on>0) {
      //cout <<"\tJ: "<< j<<", TICK:"<<tick<<endl;
      if(state[j]==1) {
        j++;
        j%=n;
        continue;
      }
      if(tick%m==0) {
        tick = 0;
        //cout << "\toff "<<j+1<<endl;
        state[j] = 1;
        on--;
        if(on==0 && j==12) {
          return m;
        }
      }
      tick++;
      j++;
      j%=n;
    }
  }
  return 0;
}
int main() {
  int n;
  do {
    cin >> n;
    if(n>=13) cout << findAns(n) << endl;
  } while(n>0);
  return 0;
}