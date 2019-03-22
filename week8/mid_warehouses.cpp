#include<cstdio>
#define MAXN 100000
int parent[MAXN+1], rank[MAXN+1];
int find(int i) {
  if(parent[i]==0) {
    return i;
  } else {
    return find(parent[i]); 
  }
}
void uni(int x,int y) {
  int a = find(x);
  int b = find(y);
  if(a==b) return;

  //printf("a %d, b %d\n",a,b);
  if(rank[a]<rank[b]) {
    parent[a] = b;
  } else if(rank[a]>rank[b]) {
    parent[b] = a;
  } else {
    parent[a] = b;
    rank[b]++;
  }
}
int min(int x,int y){
  if(x<y) return x;
  return y;
}
int max(int x,int y){
  if(x>y) return x;
  return y;
}
int n, m, k;
int main() {
  scanf("%d %d %d",&n,&m,&k);
  int x,y;
  for(int mm=0;mm<m;mm++){
    scanf("%d %d",&x,&y);
    uni(min(x,y),max(x,y));
  }

  for(int kk=0;kk<k;kk++){
    scanf("%d %d",&x,&y);
    if(find(x)==find(y)) printf("1");
    else printf("0");
    printf("\n");
  }

}