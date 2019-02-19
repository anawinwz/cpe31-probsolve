#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int node[524289];
int minnow, maxnow;
int bs(int root) {
  if(root*2 > maxnow) {
    //cout << "end at "<<root<<endl;
    return root;
  }
  if(node[root]==0) {
    node[root]=1;
    //cout << root << " go to "<<root*2<<" (left)\n";
    return bs(root*2);
  } else {
    node[root]=0;
    //cout << root << " go to "<<root*2+1<<" (right)\n";
    return bs(root*2+1);
  }
}
int findAns(int d, int ball){
  //cout <<"findAns"<<endl;
  memset(node,0,524289);
  minnow = pow(2,d-1);
  maxnow = pow(2,d)-1;
  int ans = 0;
  while(ball>0) {
    ans = bs(1);
    ball--;
  } 
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