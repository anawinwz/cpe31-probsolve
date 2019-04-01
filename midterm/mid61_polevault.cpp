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
    if(it!=sum.end()) {
      if(*it==inp) {
        printf("Y");
        continue;
      } else {
        tmp = *it;
        #ifdef debug
        printf("\t%lli(question) vs %lli(in sum) to find %lli???\n",inp,tmp,abs(inp-tmp));
        #endif
        it = find(sum.begin(),sum.end(),abs(inp-tmp));
        if(it!=sum.end()) {
          printf("Y");
          continue;
        }
      }
    } 

    bool isFound = false;
    int start = 1;
    for(int i=1;i<=n;i++) {
      for(int j=0;j<i;j++) {
        if(sum[i]-sum[j]==inp) {
          isFound = true;
          printf("Y");
          break;
        }
      }
    }
    if(isFound) continue;
    printf("N");
    
    #ifdef debug
    printf("\n");
    #endif
  }
  return 0;
}