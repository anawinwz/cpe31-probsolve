#include<iostream>
using namespace std;
int main()
{
  char str[1001];
  cin >> str;
  int i;
  for (i=0;str[i]!='\0';i++) {}
  for (--i;i>=0;i--) cout << str[i];
}
