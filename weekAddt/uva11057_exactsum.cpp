#include<iostream>
#include<algorithm>
#include<set>
#include<utility>
#include<vector>
#include<iterator>
using namespace std;
typedef pair<int,int> intpair;
int n, price;
long long int target;
bool sortme(intpair a, intpair b) {
  return abs(a.first-a.second) < abs(b.first-b.second);
}
int main() {
  vector<int> books;
  vector<intpair> cand;
  while(cin >> n) {
    books.clear();
    cand.clear();
    for(int nn=0;nn<n;nn++) {
      cin >> price;
      books.push_back(price); 
    }
    cin >> target;
    vector<int>::iterator fnd;
    for(vector<int>::iterator it=--books.end();it!=--books.begin();--it) {
      fnd = find(books.begin(),books.end(),target - *it);
      if(fnd != books.end()) {
        if(it != fnd || count(books.begin(),books.end(),*it) > 1) {
          cand.push_back(make_pair(*fnd,*it));
        }
      } 
    }
    sort(cand.begin(),cand.end(),sortme);
    int a = min(cand.begin()->first,cand.begin()->second), b  = max(cand.begin()->first,cand.begin()->second);

    cout << "Peter should buy books whose prices are " << a << " and " << b << ".\n\n";
  }
}
