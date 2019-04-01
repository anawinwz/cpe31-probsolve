#include<cstdio>
#include<set>
using namespace std;
int n, q;
int pole[1001];
set<int> alen;
int connect(int i) {
  int tmp = pole[i];
  alen.insert(pole[i]);
  if(i+1 < n) {
    tmp += connect(i+1);
    alen.insert(tmp);
  }
  return tmp;
}
int main() {
  scanf("%d %d",&n,&q);
  for(int i=0;i<n;i++) {
    scanf("%d",&pole[i]);
  }
  connect(0);
  int inp;
  for(int i=0;i<q;i++) {
    scanf("%d",&inp);
    if(alen.count(inp)!=0) printf("Y");
    else printf("N");
  }
  return 0;
}