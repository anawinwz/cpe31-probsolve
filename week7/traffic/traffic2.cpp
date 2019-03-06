#include "traffic.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>
#define debug
using namespace std;

int n,k;
int tick = 0;
int ans[2][4]={{0,0,0,0},{0,0,0,0}}, ansI=0;

int mindist(int x1, int y1, int x2, int y2) {
  int res = 0;
  res += abs(x2-x1);
  res += abs(y2-y1);
  return res;
}
main()
{
  traffic_init(&n,&k);
  int tick = 0;
  int mid, lo, hi;
  if(k==0) {
    traffic_report(
      ans[0][0],ans[0][1],ans[0][2],ans[0][3],
      ans[1][0],ans[1][1],ans[1][2],ans[1][3]
    );
  }
  for(int x=1;x<=n;x++) { // by col
    tick++;
    if(traffic_query(x,n,x,1)>n-1) {
      #ifdef debug
      cout << "Found col "<<x<<endl;
      #endif
      lo = n; hi = 1;
      while(true) {
        mid = floor((lo+hi)/2);
        #ifdef debug
        cout << lo << " << " << mid << " >> " <<hi<<endl;
        #endif
        if(tick++ && traffic_query(x,mid-1,x,mid)==2) {
          ans[ansI][0] = x;
          ans[ansI][1] = mid-1;
          ans[ansI][2] = x;
          ans[ansI++][3] = mid;  
          break;
        } else if(tick++ && traffic_query(x,mid,x,mid+1)==2) {
          ans[ansI][0] = x;
          ans[ansI][1] = mid;
          ans[ansI][2] = x;
          ans[ansI++][3] = mid+1;
          break;
        } else if(tick++ && traffic_query(x,lo,x,mid) > abs(lo-mid)) {
          hi = mid;
        } else if(tick++ && traffic_query(x,mid+1,x,hi) > abs(hi-mid-1)) {
          lo = mid+1;
        } else {
          break;
        }
      }
      if(ansI==2) break;
    }
  }
  
  if(ansI==2) {
    #ifdef debug
      cout << "ans ready!\n";
    #endif
    traffic_report(
      ans[0][0],ans[0][1],ans[0][2],ans[0][3],
      ans[1][0],ans[1][1],ans[1][2],ans[1][3]
    );
  }

  for(int y=1;y<=n;y++) { // by row
    tick++;
    if(traffic_query(1,y,n,y)>n-1) {
      #ifdef debug
      cout << "Found row "<<y<<endl;
      #endif
      lo = 1; hi = n;
      while(true) {
        mid = floor((lo+hi)/2);
        #ifdef debug
        cout << lo << " << " << mid << " >> " <<hi<<endl;
        #endif
        if(tick++ && traffic_query(mid-1,y,mid,y)==2) {
          ans[ansI][0] = mid-1;
          ans[ansI][1] = y;
          ans[ansI][2] = mid;
          ans[ansI++][3] = y;
          break;
        } else if(tick++ && traffic_query(mid,y,mid+1,y)==2) {
          ans[ansI][0] = mid;
          ans[ansI][1] = y;
          ans[ansI][2] = mid+1;
          ans[ansI++][3] = y;
          break;
        } else if(tick++ && traffic_query(lo,y,mid,y) > abs(lo-mid)) {
          hi = mid;
        } else if(tick++ && traffic_query(mid+1,y,hi,y) > abs(hi-mid-1)) {
          lo = mid+1;
        } else {
          break;
        }
      }
      if(ansI==2) break;
    }
  }
  
  #ifdef debug
  for(int i=0;i<2;i++) printf("%d, %d, %d, %d\n",ans[i][0],ans[i][1],ans[i][2],ans[i][3]);
  #endif
  traffic_report(
    ans[0][0],ans[0][1],ans[0][2],ans[0][3],
    ans[1][0],ans[1][1],ans[1][2],ans[1][3]
  );
}
 