#include<cstdio>
int ladder[1008];
int now = 0;
int min(int a, int b){
  if(a<b) return a;
  return b;
}
int max(int a, int b){
  if(a>b) return a;
  return b;
}
int main() {
  int n, m;
  scanf("%d %d",&n,&m);
  for(int nn=1;nn<=n;nn++) {
    scanf("%d",&ladder[nn]);
  }
  int dice;
  for(int mm=0;mm<m;mm++) {
    scanf("%d",&dice);
    now = min(n,now+dice);
    if(ladder[now]!=0) {
      if(ladder[now]>0) now = min(n,now+ladder[now]);
      else now = max(0,now+ladder[now]);
    }
    if(now==n) {
      break;
    }
  }
  printf("%d",now);
  return 0;
}