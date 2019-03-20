#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct shop {
  int pos;
  int price;
  int amt;
};
int n, q;
shop sh[100001];
int home;
bool sortme(shop a, shop b){
  return a.price<b.price;
}
int main() {
  scanf("%d %d",&n,&q);
  for(int i=0;i<n;i++) {
    scanf("%d %d %d",&sh[i].pos,&sh[i].price,&sh[i].amt);
  }
  sort(sh,sh+n,sortme);
  int cost;
  for(int qq=0;qq<q;qq++) {
    scanf("%d",&home);
    cost = 0;
    for(int i=0;i<n;i++) {
      if(sh[i].amt==0 || abs(sh[i].pos-home)>5) continue;
      sh[i].amt--;
      cost = sh[i].price;
      break;
    }
    printf("%d\n",cost);
  }
  return 0;
}