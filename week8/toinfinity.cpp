#include<cstdio>
#include<climits>
int min(int a,int b){
  if(b<a) return b;
  return a;
}
int main() {
  int n, minPos = INT_MAX, maxNeg = INT_MIN;
  scanf("%d",&n);
  int x, y, r, tmp;
  for(int nn=0;nn<n;nn++) {
    scanf("%d %d %d",&x,&y,&r);
    if(y>0) {
      tmp = y-r;
      if(tmp<=0) {
        printf("-1");
        return 0;
      }
      if(tmp<minPos) minPos = tmp; 
    } else if(y<0) {
      tmp = y+r;
      if(tmp>=0) {
        printf("-1");
        return 0;
      }
      if(tmp>maxNeg) maxNeg = tmp;
    } else {
      printf("-1");
      return 0;
    }
  }
  printf("%d",min(minPos,-maxNeg));
  return 0;
}