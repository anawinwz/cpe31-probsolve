#include "probelib.h"
#include <cstdlib>
#include <cstdio>

static int n;
static int target;
static int counter;

#define MAX_PROBE 22

static void probe_error(const char* msg)
{
  printf("ERROR: %s\n", msg);
  exit(0);
}

int probe_init()
{
  scanf("%d %d",&n,&target);
  counter = 0;
  return n;
}

bool probe_check(int a, int b)
{
  if((a < 0) || (a > b) || (b > n-1)) {
    probe_error("out of range");
  }
  counter++;
  if(counter > MAX_PROBE) {
    probe_error("too many checks");
  }
  return (target >= a) && (target <= b);
}

void probe_answer(int answer)
{
  if(answer == target) {
    printf("Correct\n");
  } else {
    printf("Incorrect\n");
  }
  exit(0);
}
