#include "traffic.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

int n,k;

int mindist(int x1, int y1, int x2, int y2) {
  int res = 0;
  res += abs(x2-x1);
  res += abs(y2-y1);
  return res;
}

main()
{
  traffic_init(&n,&k);
  int col = -1;
  int mid, lo, hi;
  lo = 0; hi = n-1;
  for(int x=1;x<=n;x++) { // by col
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
        if(abs(lo-mid)<=1 && abs(mid-hi)<=1) {
          #ifdef debug
          cout << lo << " "<<mid<<endl;
          #endif
          if(traffic_query(x,lo,x,mid)==2) {
            traffic_report(x,lo,x,mid,0,0,0,0);
          } else if(traffic_query(x,mid,x,hi)==2) {
            traffic_report(x,mid,x,hi,0,0,0,0);
          }
        }
        if(traffic_query(x,lo,x,mid) > abs(lo-mid)) {
          hi = mid;
        } else {
          lo = mid+1;
        }
      }
      break;
    }
  }
  for(int y=1;y<=n;y++) { // by row
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
        if(abs(lo-mid)<=1 && abs(mid-hi)<=1) {
          #ifdef debug
          cout << lo << " "<<mid<<endl;
          #endif
          if(traffic_query(lo,y,mid,y)==2) {
            traffic_report(lo,y,mid,y,0,0,0,0);
          } else if(traffic_query(mid,y,hi,y)==2) {
            traffic_report(mid,y,hi,y,0,0,0,0);
          }
        }
        if(traffic_query(lo,y,mid,y) > abs(lo-mid)) {
          hi = mid;
        } else {
          lo = mid+1;
        }
      }
      break;
    }
  }
}
