#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
struct shop {
  int pos;
  int price;
  int amt;
};
int n, q;
//vector<shop> sh;
map<int, shop> shidx;
int home;
bool sortme(shop a, shop b){
  return a.price<b.price && abs(a.pos-home)<=5 && abs(b.pos-home) > 5; 
}
bool sortidx(int a,int b) {
  return shidx[a].price<shidx[b].price; 
}
int min(int a,int b){
  if(a<b) return a;
  return b;
}
int main() {
  scanf("%d %d",&n,&q);
  for(int i=0;i<n;i++) {
    shop newsh;
    scanf("%d %d %d",&newsh.pos,&newsh.price,&newsh.amt);
    if(newsh.amt!=0) {
      //sh.push_back(newsh);
      shidx[newsh.pos] = newsh;
    }
  }
  //sort(sh.begin(),sh.end(),sortme);
  int cost;
  for(int qq=0;qq<q;qq++) {
    scanf("%d",&home);
    cost = 0;
    /*sort(sh.begin(),sh.end(),sortme);
    for(vector<shop>::iterator it=sh.begin();it!=sh.end();) {
      shop& thisshop = *it;
      if(abs(thisshop.pos-home)>5) {
        break;
      }
      //printf("%d buy from %d(): %d\n",home,thisshop.pos,thisshop.price);
      thisshop.amt--;
      cost = thisshop.price;
      if(thisshop.amt<=0) it = sh.erase(it);
      else ++it;
      break;
    }*/
    vector<int> cand;
    for(int i=max(1,home-5);i<=min(home+5,1000000000);i++) {
      if(shidx.count(i) && shidx[i].amt>0) {
        cand.push_back(i);
      }
    }
    if(!cand.empty()) {
      sort(cand.begin(),cand.end(),sortidx);
      cost = shidx[cand[0]].price;
      shidx[cand[0]].amt--;
    }
    printf("%d\n",cost);
  }
  return 0;
}