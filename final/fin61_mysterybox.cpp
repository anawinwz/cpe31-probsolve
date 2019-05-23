#include<cstdio>
int N;
char m[21][21];
//int convert(int i, int j, int drti, int drtj) {
int convert(int i, int j) {
  /*if(j==0) return i+1; //leftside
  if(j==N-1) return 3*N-i; //rightside
  if(i==0) return 4*N-j; //topside
  if(i==N-1) return N+1+j; //bottomside */
  //printf("\t[conv] %d %d\n", i , j);
  if(i<0) return 4*N-j; //topside
  if(j<0) return i+1; //leftside
  if(j==N) return 3*N-i; //rightside
  if(i==N) return N+1+j; //bottomside
}
int solve(int shoot) {
  int drt[2], pos[2]; //0-i,1-j
  if(shoot >= 3*N+1) {
    drt[0] = 1;
    drt[1] = 0;
    pos[0] = -1;
    pos[1] = 4*N-shoot;
  } else if(shoot >= 2*N+1) {
    drt[0] = 0;
    drt[1] = -1;
    pos[0] = 3*N-shoot;
    pos[1] = N;
  } else if(shoot >= N+1) {
    drt[0] = -1;
    drt[1] = 0;
    pos[0] = N;
    pos[1] = shoot-N-1;
  } else {
    drt[0] = 0;
    drt[1] = 1;
    pos[0] = shoot-1;
    pos[1] = -1;
  }
  //printf("shoot: %d startPos: %d,%d drt:%d,%d\n",shoot,pos[0],pos[1],drt[0],drt[1]);
  bool isFirst = true;
  while(isFirst || (pos[0]>=0&&pos[0]<N&&pos[1]>=0&&pos[1]<N)) {
    //printf("\t%d %d\n",pos[0],pos[1]);
    isFirst = false;
    pos[0]+=drt[0];
    pos[1]+=drt[1];
    if(!(pos[0]>=0&&pos[0]<N&&pos[1]>=0&&pos[1]<N)) break;
    //printf("\t%d %d\n",pos[0],pos[1]);
    switch(m[pos[0]][pos[1]]){
      case '\\': 
        if(drt[0]==1) { //goes down to the angle
          drt[0]=0;
          drt[1]=1;
        } else if(drt[0]==-1) {
          drt[0]=0;
          drt[1]=-1;
        } else if(drt[1]==1) {
          drt[0]=1;
          drt[1]=0;
        } else {
          drt[0]=-1;
          drt[1]=0;
        }
        //printf(" at %d %d\n",pos[0],pos[1]);
        break;
      case '/':
        if(drt[0]==1) { //goes down to the angle
          drt[0]=0;
          drt[1]=-1;
          //printf("[/] redirect left");
        } else if(drt[0]==-1) {
          drt[0]=0;
          drt[1]=1;
          //printf("[/] redirect right");
        } else if(drt[1]==1) {
          drt[0]=-1;
          drt[1]=0;
        } else {
          drt[0]=1;
          drt[1]=0;
        }
        //printf(" at %d %d\n",pos[0],pos[1]);
        break;
      default:
        break;
    }
  }
  return convert(pos[0],pos[1]);
}
int main() {
  scanf("%d",&N);
  for(int i=0;i<N;i++) scanf("%s",&m[i]);
  for(int i=1;i<=4*N;i++) printf("%d\n",solve(i)); 
  //for(int i=0;i<N;i++) printf("%d\t\t%d\n",convert(i,0),convert(i,3));
  //for(int j=0;j<N;j++) printf("%d\n\n%d\n\n",convert(0,j),convert(3,j));
}