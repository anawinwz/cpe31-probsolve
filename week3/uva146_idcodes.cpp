#include<iostream>
using namespace std;
int main() {
  char str[51], tmp;
  int maxx, len, count[26];
  while (cin >> str) {
    if (str[0] == '#' && str[1]=='\0') break;
    len = 0; maxx=0;
    for(int i=0;i<26;i++) count[i]=0;
    for(int i=0;str[i]!='\0';i++) {
      if (str[i]>maxx) maxx = str[i];
      count[str[i]-'a']++;
      len++;
    }
    for(int i=0;i<count[maxx-'a'];i++) {
      if(str[i]!=maxx) {
        maxx = 0;
        break;
      } 
    }
    if (maxx>0) {
      cout << "No Successor"<< endl; 
      continue;
    }
    for(int i=len-1-1;i>=0;i--) {
      if (str[i-1]<str[i+1] && str[i]>str[i-1] && str[i]>str[i+1]) {
        cout << "case 1 at " << i+1 << endl;
        tmp = str[i-1];
        str[i-1] = str[i+1];
        str[i+1] = str[i];
        str[i] = tmp;
        break;
      } else if(str[i]<str[i+1]) {
        cout << "case 2 at " << i+1 << endl;
        tmp = str[i+1];
        str[i+1] = str[i];
        str[i] = tmp;
        break;
      }
    }
    cout << "\t" << str << endl;
  }
}