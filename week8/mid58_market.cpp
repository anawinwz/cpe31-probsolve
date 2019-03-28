#include<cstdio>
#include<map>
using namespace std;
int n, mval = 0;
map<int, int> buy, sell;
int max(int a,int b){
  if(a>b) return a;
  return b;
}
int main() {
  scanf("%d",&n);
  int type,limit,amt;
  for(int i=0;i<n;i++) {
    scanf("%d %d %d",&type,&limit,&amt);
    switch(type) {
      case 1: //Buyer
        while(sell.begin()!=sell.end() && sell.begin()->first<=limit && amt > 0) {
          if(sell.begin()->second > amt) { //stock > buy
            mval += limit * amt;
           // printf("buy %dea price %d\n",amt,limit);
            sell.begin()->second -= amt;
            if(sell.begin()->second==0) sell.erase(sell.begin());
            amt = 0;
          } else {
            mval += limit * sell.begin()->second;
            //printf("buy %dea price %d\n",sell.begin()->second,limit);
            amt -= sell.begin()->second;
            sell.erase(sell.begin());
          }
        }
        if(amt > 0) {
          //printf("add buyer %dea limit: %d\n",amt,limit);
          if(!buy.count(limit)) buy[limit] = 0;
          buy[limit] += amt;
        }
        break;
      case 2: //Seller
        for(map<int,int>::reverse_iterator it=buy.rbegin(); amt > 0 && it!=buy.rend() && it->first >= limit; ) {
          if(it->second <= 0) {
            ++it;
            continue;
          }

          if(amt < it->second) {
            mval += limit * amt;
          //  printf("sell %dea price %d\n",amt,limit);
            it->second -= amt;
            amt = 0;
            break;
          } else {
            mval += limit * it->second;
          //  printf("sell %dea price %d\n",it->second,limit);
            amt -= it->second;
            it->second = 0;
            //buy.erase(it++);
          }
        }
        if(amt > 0) {
        //  printf("add seller %dea limit: %d\n",amt,limit);
          if(!sell.count(limit)) sell[limit] = 0;
          sell[limit] += amt;
        }
        break;
    }
  }
  printf("%d",mval);
  return 0;
}