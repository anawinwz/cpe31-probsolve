#include<cstdio>
int parent[100001], rnk[100001]; 
int find(int i) {
  if(parent[i]==0) {
    return i;
  } else {
    return find(parent[i]); 
  }
}
bool uni(int x,int y) {
  int a = find(x);
  int b = find(y);
  if(a==b) return false;

  if(rnk[a]<rnk[b]) {
    parent[a] = b;
  } else if(rnk[a]>rnk[b]) {
    parent[b] = a;
  } else {
    parent[a] = b;
    rnk[b]++;
  }
  return true;
}
int n, q;
int main() {
  scanf("%d %d",&n,&q);
  char m; int a,b;
  for(int qq=0;qq<q;qq++) {
    scanf(" %c %d %d",&m,&a,&b);
    switch(m){
      case 'q':
        printf("%s\n",(find(a)==find(b)?"yes":"no"));
        break;
      case 'c':
        uni(a,b);
        break;
    }
  }
}