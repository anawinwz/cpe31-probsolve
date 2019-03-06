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
  int midx, midy, lox, loy, hix, hiy;
  lox = 1; loy=n; hix=n; hiy=1;
  while(true) {
    midx = ceil((lox+hix)/2);
    midy = ceil((loy+hiy-1)/2);
    cout << lox<<","<<loy<<"\t<<"<<midx<<","<<midy<<">>\t"<<hix<<","<<hiy<<"\n";

    if(mindist(lox,loy,hix,hiy)==1) {
      cout << "Found at "<<midx<<","<<midy<<endl;
      traffic_report(lox,loy,hix,hiy,0,0,0,0);
    }
    if(lox>midx || loy<midy) {
      cout << "Low exceed!\n Mid: "<<midx<<","<<midy<<endl;
      cout << "Low: "<<lox<<","<<loy<<endl;
      traffic_report(-1,-1,-1,-1,0,0,0,0);
    }

    printf("(%d,%d)\t\t\t\t(%d,%d)\n",lox,loy,midx+1,loy);
    printf("\t\t(%d,%d)\t\t\t(%d,%d)\n",midx,midy+1,hix,midy+1);
    printf("(%d,%d)\t\t\t\t(%d,%d)\n",lox,midy,midx+1,midy);
    printf("\t\t(%d,%d)\t\t\t(%d,%d)",midx,hiy,hix,hiy);
    int dist, dist2;
    if((dist = traffic_query(lox,loy,midx,midy+1)) > (dist2=mindist(lox,loy,midx,midy+1))) { //Q1
      cout << "Go to Q1 Dist: "<<dist<<","<<dist2 <<endl;
      hix = midx;
      hiy = midy+1;
    } else if((dist = traffic_query(midx+1,loy,hix,midy+1)) > (dist2=mindist(midx+1,loy,hix,midy+1))) { //Q2
      cout << "Go to Q2 Dist: "<<dist<<","<<dist2 <<endl;
      lox = midx+1;
      hiy = midy+1;
    } else if((dist = traffic_query(lox,midy,midx,hiy)) > (dist2=mindist(lox,midy,midx,hiy))) { //Q3
      cout << "Go to Q3 Dist: "<<dist<<","<<dist2 <<endl;
      hix = midx;
      //hiy = midy;
    } else if((dist = traffic_query(midx+1,midy,hix,hiy)) > (dist2=mindist(midx+1,midy,hix,hiy))) {
      cout << "Go to Q4 Dist: "<<dist<<","<<dist2 <<endl;
      lox = midx+1;
      //hiy = midy; 
    } else {
      cout << "Impossible! Dist: "<<dist<<","<<dist2 << endl;
      break;
    }
  }
}
