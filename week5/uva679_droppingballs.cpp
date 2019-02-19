#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int minnow, maxnow;
int bs(int root, int ball) {
  if(root*2 > maxnow) {
    //cout << "end at "<<root<<endl;
    return root;
  }
  if(ball%2==1) {
    //cout << root << " go to "<<root*2<<"\n";
    return bs(root*2,ball/2+1);
  } else {
    //cout << root << " go to "<<root*2+1<<" (right)\n";
    return bs(root*2+1,ball/2);
  }
}
int findAns(int d, int ball){
  //cout <<"findAns"<<endl;
  int ans = 0;
  minnow = pow(2,d-1);
  maxnow = pow(2,d)-1;
  ans = bs(1,ball);
  return ans;
}
int main() {
  ios::sync_with_stdio(false);
  int t, d, i, tmp;
  cin >> t;
  for(int tt=0;tt<t;tt++) {
    cin >> d >> i;
    cout << findAns(d,i) << endl;
  }
  cin >> t;
  return 0;
}