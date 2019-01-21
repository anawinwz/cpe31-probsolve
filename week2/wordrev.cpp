#include<iostream>
using namespace std;
char str[1001];
void rev(int start, int end) {
  for(int i=end-1;i>=start;i--) cout << str[i];
}
int main() {
  int start = 0,i;
  cin >> str;
  for(i=0;str[i]!='\0';i++) {
    if(str[i]=='_') {
      rev(start,i);
      start = i+1;
      cout << '_';
    }
  }
  rev(start,i);
  return 0;
}