#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;
int a,b;
int max(int a,int b){
  if(a>b) return a;
  return b;
}
int min(int a,int b){
  if(a<b) return a;
  return b;
}
bool isPrime(int n) {
  if(n==1) return false;

  for(int i=2;i<=sqrt(n);i++) {
    if(n!=i && n%i==0) return false;
  }
  return true;
}
vector<int> primes;
int main() {
  scanf("%d %d",&a,&b);
  for(int i=a;i<=b;i++) {
    if(isPrime(i)) primes.push_back(i);
  }
  int ans = 0;
  for(int i=1;i<primes.size();i++) {
    if(primes[i]-primes[i-1]==2) ans++;
  }
  printf("%d",ans);

  return 0;
}