#include<cstdio>
int n;
int p[100001];
long long int dp[100001];
int main() {
  scanf("%d",&n);
  for(int i=1;i<=n;i++) scanf("%d",&p[i]);
  dp[0] = 0;
  dp[1] = p[1];
  dp[2] = p[2];
  long long int bestdp = 0;
  for(int i=3;i<=n;i++) {
    if(dp[i-3] > bestdp) bestdp = dp[i-3];
    dp[i] = p[i] + bestdp;
  }
  long long int maxdp = 0;
  for(int i=0;i<=n;i++) {
    if(dp[i]>maxdp) maxdp = dp[i];
  }
  printf("%lli", maxdp);
  return 0;
}