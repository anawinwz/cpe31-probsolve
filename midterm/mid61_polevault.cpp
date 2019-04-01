#include<cstdio>
#include<vector>
#include<algorithm>
//#define debug
using namespace std;
vector<long long int> sum;
int n,q;
int main() {
  long long int inp;
  sum.push_back(0);
  scanf("%d %d",&n,&q);
  for(int i=0;i<n;i++) {
    scanf("%lli",&inp);
    sum.push_back(sum[i]+inp);
  }
  vector<long long int>::iterator it;
  long long int tmp;
  for(int i=0;i<q;i++) {
    scanf("%lli",&inp);
    it = lower_bound(sum.begin(),sum.end(),inp);
    if(it==sum.end()) {
      printf("N");
      continue;
    }
    
    if(*it==inp) {
      printf("Y");
    } else {
      tmp = *it;
      #ifdef debug
      printf("\t%lli(question) vs %lli(in sum) to find %lli???\n",inp,tmp,abs(inp-tmp));
      #endif
      it = find(sum.begin(),sum.end(),abs(inp-tmp));
      if(it!=sum.end()) printf("Y");
      else {
        bool isFound = false;
        for(int i=n;i>=1;i--) {
          for(int j=1;j<i;j++) {
            if(sum[i]-sum[j]==inp) {
              isFound = true;
              printf("Y");
              break;
            }
          }
        }
        if(isFound) continue;
        printf("N");
      }
    }
    #ifdef debug
    printf("\n");
    #endif
  }
  return 0;
}