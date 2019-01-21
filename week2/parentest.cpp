#include<iostream>
using namespace std;
bool match(char a,char b) {
  char m;
  switch(a) {
    case '{':m='}';break;
    case '[':m=']';break;
    case '(':m=')';break;
    default:m='\0';
  }
  if(b==m) return true;
  return false;
}
int main(){
  int t, si, isBreak;
  cin >> t;
  char str[101], stack[101];
  for(int tt=0;tt<t;tt++) {
    si = 0;
    isBreak = 0;
    cin >> str;
    for(int i=0;str[i]!='\0';i++) {
      switch(str[i]) {
        case '{':
        case '[':
        case '(':
          stack[si++] = str[i];
          break;
        default:
          if(si <= 0 || !match(stack[si-1],str[i])) {
            cout << "no";
            isBreak = 1;
          } else {
            si--;
          }
      }
      if (isBreak) break;
    }
    if(!isBreak) {
      if(si==0) cout << "yes";
      else cout << "no";
    }
    cout << endl;
  }

  return 0;
}