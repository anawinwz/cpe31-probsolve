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
      printf("\t%d(question) vs %d(in sum) to find %d\n",inp,tmp,tmp-inp);
      #endif
      it = find(sum.begin(),sum.end(),tmp-inp);
      if(it!=sum.end()) printf("Y");
      else printf("N");
    }
    #ifdef debug
    printf("\n");
    #endif
  }
  return 0;
}