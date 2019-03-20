#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
struct shop {
  int pos;
  int price;
  int amt;
};
int n, q;
vector<shop> sh;
int home;
bool sortme(shop a, shop b){
  return a.price<b.price;
}
int main() {
  scanf("%d %d",&n,&q);
  for(int i=0;i<n;i++) {
    shop newsh;
    scanf("%d %d %d",&newsh.pos,&newsh.price,&newsh.amt);
    sh.push_back(newsh);
  }
  sort(sh.begin(),sh.end(),sortme);
  int cost;
  for(int qq=0;qq<q;qq++) {
    scanf("%d",&home);
    cost = 0;
    for(vector<shop>::iterator it=sh.begin();it!=sh.end();) {
      shop& thisshop = *it;
      if(thisshop.amt==0 || abs(thisshop.pos-home)>5) {
        ++it;
        continue;
      }
      //printf("%d buy from %d(): %d\n",home,thisshop.pos,thisshop.price);
      thisshop.amt--;
      cost = thisshop.price;
      if(thisshop.amt<=0) it = sh.erase(it);
      else ++it;
      break;
    }
    printf("%d\n",cost);
  }
  return 0;
}