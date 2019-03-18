#include<cstdio>
bool isVowel(char a){
  switch(a){
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      return true;
      break;
  }
  return false;
}
int main() {
  int n;
  scanf("%d",&n);
  char str[31];
  bool isV = false;
  int cnt;
  for(int i=0;i<n;i++) {
    scanf("%s",&str);
    isV = false; cnt = 0;
    for(int si=0;str[si]!='\0';si++){
      if(isVowel(str[si])) {
        if(!isV) {
          isV = true;
          cnt++;
        }
      } else isV = false;
    }
    printf("%d\n",cnt);
  }

  return 0;
}