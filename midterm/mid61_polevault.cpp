/*
TASK: mid61_polevault
LANG: C++
*/
#include<cstdio>
#include<set>
using namespace std;
int n, q;
int pole[1001];
set<int> alen;
void connect(int i, int now) {
  if(i>=n) return;

  //pick
  alen.insert(now+pole[i]);
  connect(i+1,now+pole[i]); 
  //notpick
  alen.insert(now); 
}
int main() {
  scanf("%d %d",&n,&q);
  for(int i=0;i<n;i++) {
    scanf("%d",&pole[i]);
  }
  for(int i=0;i<n;i++) { 
    connect(i,0);
  }
  int inp;
  for(int i=0;i<q;i++) {
    scanf("%d",&inp);
    if(alen.count(inp)!=0) printf("Y");
    else printf("N");
  }
  return 0;
}