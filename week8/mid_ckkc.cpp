#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

int main() {
  int x;
  scanf("%d",&x);
  int skipyr[1001], skipyrI=0;
  int inp;
  while(true) {
    scanf(" %d",&inp);
    if(inp==0) break;

    skipyr[skipyrI++] = inp;
  }
  sort(skipyr,skipyr+skipyrI);
  
  char curU = 'K';
  int curYear = 2558;
  for(int i=0;i<skipyrI;i++) {
    if((skipyr[i]-curYear)%2==1) {
      if(curU=='K') curU = 'C';
      else curU = 'K';
    }
    curYear = skipyr[i]+1;
    //printf("%c - %d\n",curU,curYear);
  }
  if((x-curYear)%2==1) {
    if(curU=='K') curU = 'C';
    else curU = 'K';
  }
  printf("%c",curU);
}