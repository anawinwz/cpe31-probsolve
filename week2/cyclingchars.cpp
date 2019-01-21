#include<iostream>
using namespace std;
char rotate(char a) {
  int tmp = (a+4) % ('z'+1);
  if (tmp < 'a') return tmp + 'a';
  return tmp;
}
int main() {
  char str[101];
  cin >> str;
  for(int i=0;str[i]!='\0';i++) cout << rotate(str[i]);
}