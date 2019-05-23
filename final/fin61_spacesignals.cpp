#include<cstdio>
#include<cstring>
char S[21], T[200001];
int main() {
  scanf("%s",&S);
  scanf("%s",&T);
  int si=0, ans=0, slen=strlen(S), tlen=strlen(T);
  for(int i=0;i<tlen;i++) {
    if(T[i]==S[si]) {
      si++;
      if(si==slen) {
        ans++;
        si = 0;
      }
    }
  }
  printf("%d",ans);
}