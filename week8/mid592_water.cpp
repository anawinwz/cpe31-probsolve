#include<cstdio>
int abs(int a,int b){
  int tmp=a-b;
  if(tmp<0) return -tmp;
  else return tmp;
}
int minprod(int a, int b){
  if(a<b) return a;
  else return b;
}
int main() {
  int n; 
  scanf("%d",&n);
  int sum = 0, prev = 0, today;
  for(int i=0;i<n;i++) {
    scanf("%d",&today);
    if(prev-today>10) {
      sum += minprod(700,(prev-today)*10);
    }
    prev = today;
  }
  printf("%d",sum);
  return 0;
}