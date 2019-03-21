#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int n, pn=0;
typedef struct person {
  int seller;
  int amt;
  int price;
};
person p[100000];
vector<int> waitbuy;
vector<int> waitsell;
int mval = 0, sellaval = 0;
bool sortseller(int a, int b) {
  return p[a].price < p[b].price;
}
bool sortbuyer(int a, int b) {
  return p[a].price > p[b].price;
}
int max(int a,int b){
  if(a>b) return a;
  return b;
}
int min(int a,int b){
  if(a<b) return a;
  return b;
}
vector<int>::iterator buy_waitsell(int i,vector<int>::iterator it) {
  //==== BUYER come in ====
  //buy price <= P
  int A = p[i].amt, P = p[i].price;

  int sellcnt = waitsell.size();
  sort(waitsell.begin(),waitsell.end(),sortseller);

  int thisaval = 0;
  //vector<int> candidate;
  for(vector<int>::iterator it=waitsell.begin();it!=waitsell.end();++it) {
    if(p[*it].price > P) break;
    //candidate.push_back(*it);
    thisaval += p[*it].amt;
  }

  if(thisaval < A) {
    waitbuy.push_back(i);
    return waitbuy.end(); 
  } 
  
  for(vector<int>::iterator it=waitsell.begin();it!=waitsell.end();++it) {
    if(p[*it].price > P) break;
    
    
    if(p[*it].amt > A) {
      mval += p[*it].price * A;
      p[*it].amt -= A;
      A = 0;
      waitsell.erase(it);
      break; 
    } else {
      mval += p[*it].price * p[*it].amt;
      A -= p[*it].amt;
      p[*it].amt = 0;
    }
  }
  
  sellaval -= A;

  vector<int>::iterator res;
  if( (res=find(waitbuy.begin(),waitbuy.end(),i)) != waitbuy.end() ) {
    return waitbuy.erase(res); 
  } else return ++it;  
}

vector<int>::iterator sell_waitbuy(int i,vector<int>::iterator it) {
  //==== SELLER come in ====
  //sell price >= Q
  //stock B, 
  int B = p[i].amt, Q = p[i].price;

  int buycnt = waitbuy.size();
  sort(waitbuy.begin(),waitbuy.end(),sortbuyer); 
  
  for(vector<int>::iterator it=waitbuy.begin();it!=waitbuy.end();) {
    if(p[*it].price < Q) break;
    
    if(p[*it].amt <= B) {
      mval += max(p[*it].price,Q) * p[*it].amt;
      B -= p[*it].amt;
      p[*it].amt = 0;
      it = waitbuy.erase(it);
    } else {
      ++it;
    }
  }
  
  if(B>0) {
    sellaval += B;
    waitsell.push_back(i);
  }

}

int main() {
  scanf("%d",&n);
  int seller, a, b;
  for(int i=0;i<n;i++) {
    scanf("%d %d %d",&seller,&a,&b);
    p[i].seller=--seller;
    p[i].amt=b;
    p[i].price=a;
    switch(p[i].seller) {
      case 0:
        if(waitsell.size()==0 || sellaval<b) {
          waitbuy.push_back(i);
        } else {
          buy_waitsell(i, waitsell.end());
        }
        break;
      case 1:
        if(waitbuy.size()==0) {
          waitsell.push_back(i);
          sellaval+=a;
        } else {
          sell_waitbuy(i, waitbuy.end());
        }
        break;
    }
    //printf("\t Current mval: %d, Waiting buyer: %d, Waiting seller: %d\n",mval,waitbuy.size(),waitsell.size());
  }
  printf("%d",mval);
  return 0;
}