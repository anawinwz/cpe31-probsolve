#include "probelib.h"
#include <cstdio>
#include <cmath>

int n;

main()
{
  int n = probe_init();
  int mid, lo, hi;
  lo = 0; hi = n-1;
  while(true) {
    mid = floor((lo+hi)/2);
    if(probe_check(lo,mid)) {
      if(lo==mid) probe_answer(lo);
      hi = mid;
    } else {
      lo = mid+1;
    }
  }

}
