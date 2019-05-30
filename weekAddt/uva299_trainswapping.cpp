#include<cstdio>
#include<cstring>
int train[51];
int read_inp(){
  int n;
  scanf("%d",&n);
  for(int i=0;i<n;i++) {
    scanf("%d",&train[i]);
  }
  return n;
}
int process() {
  memset(train, 0, sizeof(train));
  int cnt = 0, n = read_inp(), tmp;
  bool swapped = false;
  do {
    swapped = false;
    for(int i=1;i<n;i++) {
      if(train[i-1]>train[i]) {
        tmp = train[i-1];
        train[i-1] = train[i];
        train[i] = tmp;
        swapped = true;
        cnt++;
      }
    }
  } while(swapped);
  return cnt;
}
int main() {
  int t;
  scanf("%d",&t);
  for(int tt=0;tt<t;tt++) printf("Optimal train swapping takes %d swaps.\n",process());
  return 0;
}