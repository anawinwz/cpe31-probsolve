#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int x[1201], n;
bool sortme(int a, int b){
  return x[a]>x[b];
}
void printVec(vector<int> a) {
  for(vector<int>::iterator it=a.begin();it!=a.end();++it) {
    printf("%d ",*it);
  }
  printf("\n------------------------\n");
}
int main() {
  scanf("%d",&n);
  vector<int> person;
  for(int nn=0;nn<4*n;nn++){
    scanf("%d",&x[nn]);
    person.push_back(nn);
  }
  
  vector<int> rnd1(person.begin(),person.begin()+n);
  vector<int> rnd2(person.begin()+n,person.begin()+2*n);
  vector<int> rnd3(person.begin()+2*n,person.begin()+3*n);
  vector<int> rnd4(person.begin()+3*n,person.begin()+4*n);

  sort(rnd1.begin(), rnd1.end(), sortme);
  sort(rnd2.begin(), rnd2.end(), sortme);
  sort(rnd3.begin(), rnd3.end(), sortme);
  sort(rnd4.begin(), rnd4.end(), sortme);
  /*printVec(rnd1);
  printVec(rnd2);
  printVec(rnd3);
  printVec(rnd4);*/

  int losta, wina, lostb, winb;
  if(x[rnd1[0]]>x[rnd2[0]]) {
    wina = rnd1[0];
    losta = rnd2[0];
  } else {
    wina = rnd2[0];
    losta = rnd1[0];
  }
  if(x[rnd3[0]]>x[rnd4[0]]) {
    winb = rnd3[0];
    lostb = rnd4[0];
  } else {
    winb = rnd4[0];
    lostb = rnd3[0];
  }

  printf("%d %d %d %d",(x[wina]>x[winb])?wina+1:winb+1,(x[wina]<x[winb])?wina+1:winb+1,losta+1,lostb+1);

  return 0;
}