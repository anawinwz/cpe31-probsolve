#include<cstdio>
#include<cmath>
using namespace std;
int north[3002], south[3002], n;
int ans = 0;
void print(int si, int ei) {
  printf("north: ");
  for(int i=si;i<=ei;i++) {
    printf("%d ",north[i]);
  }
  printf("\nsouth: ");
  for(int i=si;i<=ei;i++) {
    printf("%d ",south[i]);
  }
  printf("\n");
}
void match(int si, int ei) {
  //print(si,ei);
  if(abs(si-ei)>2) {
    int mid = floor((si+ei)/2);
    match(si, mid);
    match(mid+1, ei);
    if(north[mid]==south[mid+1]) ans++;
  } else {
    for(int i=si;i<=ei;i++) {
      for(int j=si;j<=ei;j++) {
        if(north[i]==south[j]) ans++;
      }
    }
  }
}
int main() {
  scanf("%d",&n);
  for(int i=0;i<n;i++) {
    scanf("%d",&north[i]);
  }
  for(int i=0;i<n;i++) {
    scanf("%d",&south[i]);
  }
  match(0,n-1);
  printf("%d",ans);
  return 0;
}