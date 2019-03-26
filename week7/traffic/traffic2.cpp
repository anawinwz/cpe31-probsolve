#include "traffic.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>
//#define debug
using namespace std;
int n, k;
int ans[2][4] = {{0,0,0,0},{0,0,0,0}}, ansI=0;
bool isAns(int x1, int y1, int x2, int y2) {
  for(int i=0;i<ansI;i++) {
    if((ans[i][0]==x1&&ans[i][1]==y1&&ans[i][2]==x2&&ans[i][3]==y2) || (ans[i][0]==x2&&ans[i][1]==y2&&ans[i][2]==x1&&ans[i][3]==y1)) return true;
  }
  return false;
}
void addAns(int x1, int y1, int x2, int y2) {
  if(ansI==2 || isAns(x1,y1,x2,y2)) return;
  ans[ansI][0] = x1;
  ans[ansI][1] = y1;
  ans[ansI][2] = x2;
  ans[ansI++][3] = y2;
}
void findCol(int y, int sx, int ex){
  if(ansI==k) return;

  int lo = sx, hi = ex, mid;
  mid = floor(abs(hi+lo)/2);
  int total = traffic_query(lo,y,hi,y);
  #ifdef debug
  printf("findCol(%d,%d,%d)\n",y,sx,ex);
  printf("\t%d << %d >> %d\n",lo,mid,hi);
  #endif
  /*if(traffic_query(mid-1,y,mid,y)==2) {
    addAns(mid-1,y,mid,y);
  } else if(traffic_query(mid,y,mid+1,y)==2) {
    addAns(mid,y,mid+1,y);
  } else {*/
  if(abs(lo-hi)==1 && total==2) {
    addAns(lo,y,hi,y);
  } else if(total <= abs(lo-hi)) {
    return;
  } else {
    if(traffic_query(lo,y,mid,y) > abs(lo-mid)) findCol(y, lo, mid);
    else findCol(y, mid, hi);
  }
 //}
}
void findRow(int x, int sy, int ey){
  if(ansI==k) return;

  int lo = sy, hi = ey, mid;
  mid = floor(abs(hi+lo)/2);
  int total = traffic_query(x,lo,x,hi);
  #ifdef debug
  printf("findRow(%d,%d,%d)\n",x,sy,ey);
  printf("\t%d << %d >> %d\n",lo,mid,hi);
  #endif
  /*if(traffic_query(x,mid-1,x,mid)==2) {
    addAns(x,mid-1,x,mid);
  } else if(traffic_query(x,mid,x,mid+1)==2) {
    addAns(x,mid,x,mid+1);
  */
  if(abs(lo-hi)==1 && total==2) {
    addAns(x,lo,x,hi);
  } else if(total <= abs(lo-hi)) {
    return;
  } else {
    if(traffic_query(x,lo,x,mid) > abs(lo-mid)) findRow(x, lo, mid);
    else findRow(x, mid, hi);
  }
}
main()
{
  traffic_init(&n,&k);
  int tick = 0;
  for(int y=1;y<=n;y++) { // by row
    findCol(y, 1, n);
  }
  for(int x=1;x<=n;x++) { // by row
    findRow(x, 1, n);
  }

  #ifdef debug
  for(int i=0;i<2;i++) printf("ans: %d, %d, %d, %d\n",ans[i][0],ans[i][1],ans[i][2],ans[i][3]);
  #endif
  traffic_report(
    ans[0][0],ans[0][1],ans[0][2],ans[0][3],
    ans[1][0],ans[1][1],ans[1][2],ans[1][3]
  );

}
 