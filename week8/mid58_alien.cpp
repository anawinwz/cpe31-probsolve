#include<cstdio>
#include<cmath>
int main() {
  int n, a, b, r;
  scanf("%d %d %d %d",&n,&a,&b,&r);
  //printf("(%d,%d) r: %d\n",a,b,r);
  int ans=0, tmp, x, y;
  for(int i=0;i<n;i++) {
    scanf("%d %d",&x,&y);
    tmp = pow(x-a,2)+pow(y-b,2);
    //printf("\t%d\n",tmp);
    if(tmp<=r*r) {
      ans++;
    }
  }
  printf("%d",ans);
  return 0;
}