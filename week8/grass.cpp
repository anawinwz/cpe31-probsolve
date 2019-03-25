#include<cstdio>
int n, m;
char map[101][101];
void rowOp(int i, char cmd, char upd) {
  bool isBlock = (cmd=='A')?false:true;
  int j = (cmd=='R') ? n-1:0;
  while(j>=0 && j<n) {
    if(isBlock && (map[i][j]=='#' || map[i][j]=='.')) break;

    if(map[i][j]!='#') map[i][j] = upd;

    if(cmd=='R') j--; 
    else j++;
  }
}
void colOp(int j, char cmd, char upd) {
  bool isBlock = (cmd=='B')?false:true;
  int i = (cmd=='D') ? n-1:0;
  while(i>=0 && i<n) {
    if(isBlock && (map[i][j]=='#'|| map[i][j]=='.')) break;

    if(map[i][j]!='#') map[i][j] = upd;

    if(cmd=='D') i--; 
    else i++;
  }
}
int main() {
  scanf("%d %d",&n,&m);
  for(int i=0;i<n;i++) {
    scanf("%s",&map[i]);
  }
  char cmd; int k;
  for(int mm=0;mm<m;mm++) {
    scanf(" %c %d",&cmd,&k);
    switch(cmd) {
      case 'L':
      case 'R':
      case 'A':
        rowOp(k-1,cmd,(cmd=='A')?'x':'.');
        break;
      case 'U':
      case 'D':
      case 'B':
        colOp(k-1,cmd,(cmd=='B')?'x':'.');
        break;
    }
  }
  for(int i=0;i<n;i++)  printf("%s\n",map[i]);
  return 0;
}