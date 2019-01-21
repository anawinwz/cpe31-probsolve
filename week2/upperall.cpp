#include<iostream>
using namespace std;
char toupper(char s) {
  if (s >= 'a' && s <= 'z') return (char)(s-32);
  else return s;
}
int main() {
  char str[101];
  cin >> str;
  for(int i=0;str[i]!='\0';i++) cout << toupper(str[i]);
}