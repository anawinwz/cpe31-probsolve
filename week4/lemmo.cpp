#include<cstdio>
#include<cstring>
#include<list>
#include<vector>
#include<utility>
//#define debug true
#define MAXN 120
using namespace std;
vector< pair<int,int> > flrlist;
char map[MAXN+1][MAXN+1];

int ans1=0, ans2=0;

int n, m;

bool visited[MAXN+1][MAXN+1];
bool isWorked[MAXN+1][MAXN+1];
int afterClose[MAXN+1][MAXN+1];
int result[2][MAXN+1][MAXN+1];

bool bfs(int si, int sj, int drt, bool isCnt, char (&map)[MAXN+1][MAXN+1]);
bool bfs(int sj, int sdrt) {
  return bfs(0, sj, sdrt, true, map); 
}
bool bfs(int sj, int sdrt, bool isCnt, char (&map)[MAXN+1][MAXN+1]) {
  return bfs(0, sj, sdrt, isCnt, map);
}
bool bfs(int si, int sj, int sdrt, bool isCnt, char (&map)[MAXN+1][MAXN+1]){
  //drt: 1-forward 0-backward
  int drt = sdrt;
  #ifdef debug
  printf("--------- bfs(%d,%d,%d) ------------\n",si,sj,drt);
  #endif
  if(result[sdrt][si][sj]==1) {
    #ifdef debug
      printf("Memorization at First\n");
    #endif
    return true;
  }
  bool ret = false;
  if(isCnt) {
    for(int i=0;i<n;i++) {
      for(int j=0;j<m;j++) {
        visited[i][j] = false;
        isWorked[i][j] = false;
        //layer[i][j] = -1;
      }
    }
  }
  
  //layer[si][sj] = 0;
  pair<int,int> v;
  list< pair< pair<int,int>, pair<int,int> > > Q;
  Q.push_back(make_pair(make_pair(si,sj),make_pair(-1,-1)));
  int flrn = flrlist.size();
  for(int flrnn=0;flrnn<flrn;flrnn++) {
    v = flrlist[flrnn];
    if((v.first==si&&((sdrt==1&&v.second<sj)||(sdrt==0&&v.second>sj))) || result[drt][v.first][v.second]==1) continue;
    Q.push_back(make_pair(make_pair(si,sj),make_pair(v.first,v.second)));
  }
  while(!Q.empty()) {
    pair< pair<int,int>, pair<int,int> > elm = Q.front();
    pair<int,int> u = elm.first;
    Q.pop_front();

    /*
    if(isCnt && !realVisited[u.first][u.second] && u.first<n-1 && map[u.first][u.second]=='#') {
      //printf("not visited %d %d\n",u.first,u.second);
      flrlist.push_back(make_pair(u.first, u.second));
    }*/

    //Check if this turn off works?
    if(elm.second.first!=-1) {
      if(isWorked[elm.second.first][elm.second.second]==true) continue;
      else if(result[drt][u.first][u.second]==1) {
        #ifdef debug
        printf("Memorized after disabled %d %d! Now: %d\n",elm.second.first,elm.second.second,afterClose[elm.second.first][elm.second.second]+1);
        #endif
        isWorked[elm.second.first][elm.second.second] = true;
        afterClose[elm.second.first][elm.second.second]++;
        if(afterClose[elm.second.first][elm.second.second]>ans2) ans2 = afterClose[elm.second.first][elm.second.second];
        continue;
      }
    } else {
      if(result[drt][u.first][u.second]==1) {
        #ifdef debug
        printf("\tUse memorization at %d %d\n",u.first,u.second);
        #endif
        ret = true;
        continue;
      }
    }
    #ifdef debug
    printf("now %d %d\t",u.first,u.second);
    if(elm.second.first!=-1) printf(" (skipped %d,%d)",elm.second.first, elm.second.second);
    printf("\n");
    #endif

    visited[u.first][u.second] = true;
    vector< pair<int,int> > adj;
    switch(map[u.first][u.second]) {
      case '$': 
        if(elm.second.first==-1) {
          ret = true;
          result[drt][u.first][u.second] = 1;
        } else {
          #ifdef debug
          printf("Finally after disabled %d %d! Now: %d\n",elm.second.first,elm.second.second,afterClose[elm.second.first][elm.second.second]+1);
          #endif
          isWorked[elm.second.first][elm.second.second] = true;
          afterClose[elm.second.first][elm.second.second]++;
          if(afterClose[elm.second.first][elm.second.second]>ans2) ans2 = afterClose[elm.second.first][elm.second.second];
        }
        continue;
      case '@':
        if(result[drt][u.first][u.second]!=1) result[drt][u.first][u.second] = 2;
        continue;
      case '.':
        if(u.first+1<n) adj.push_back(make_pair(u.first+1, u.second));
      break;
      default:
        if(u.first==elm.second.first && u.second==elm.second.second) {
          if(u.first+1<n) adj.push_back(make_pair(u.first+1, u.second));
        }
        else
        switch(drt) {
          case 0: //backward
            if(u.second-1>=0) adj.push_back(make_pair(u.first, u.second-1));
            else {
              drt = 1;
              //printf("Switch direction to %d at %d %d.\n",drt,u.first,u.second);
              adj.push_back(make_pair(u.first, u.second+1));
            }
          break;
          case 1: //forward
            if(u.second+1<m) adj.push_back(make_pair(u.first, u.second+1));
            else {
              drt = 0;
              //printf("Switch direction to %d at %d %d.\n",drt,u.first,u.second);
              adj.push_back(make_pair(u.first, u.second-1));
            }
          break;
        }
    }
    

    int deg = adj.size();
    for(int i=0;i<deg;i++) {
      v = adj[i];
      switch(map[v.first][v.second]) {
        case '.':v.first++;break;
      }
        
      //if(layer[v.first][v.second]==-1) {
      if(v.first<n) {
        //layer[v.first][v.second]=layer[u.first][u.second]+1;
        Q.push_back(make_pair(make_pair(v.first, v.second), elm.second));
        //if(elm.second.first==-1 && v.first+1<n && result[drt][v.first][v.second]!=1 && map[v.first][v.second]=='#')
        //  Q.push_back(make_pair(make_pair(v.first+1, v.second), make_pair(v.first, v.second)));
      } 
    }
    
  }
  if(ret) {
    result[sdrt][si][sj] = 1;
    ans1++;
  }
  return ret;
}

void read_input() {
  scanf("%d %d",&m,&n);
  for(int i=0;i<n;i++) {
    scanf("%s",map[i]);
  }
}

int main() {
  read_input();
  int rewardCnt = 0;
  for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
      if(map[i][j]=='#') flrlist.push_back(make_pair(i,j));
      if(map[n-1][j]=='$') rewardCnt++;
    }
  }
  if(rewardCnt==0) {
    printf("0 0");
    return 0;
  }
  for(int j=0;j<m;j++) {
    bfs(j,0);
    bfs(j,1);
  }
  
  /*
  int thisans = 0;
  if(n==1) maxAns = ans;
  else {
    int flrn = flrlist.size(), i, j;
    pair<int,int> flr;
    //printf("flrn: %d\n",flrn);
    for(int flrnn=0;flrnn<flrn;flrnn++) {
      flr = flrlist[flrnn];
      i = flr.first; j = flr.second;
      //printf("flrnn %d, i j %d %d\n",flrnn,i,j);
      map[i][j]='.';
      thisans = 0;
      for(int k=0;k<m;k++) {
        if(bfs(k,'<',false,map)) thisans++;
        if(bfs(k,'>',false,map)) thisans++;
      }
      
      //printf("try to disable %d %d\told visitCnt: %d\n",i,j,visitCnt[i][j]);
      
     // printf("after disable %d %d: %d\n",i,j,thisans);
      if(thisans>maxAns) maxAns = thisans;
      map[i][j]='#';
    }
  }*/
  if(n==1) ans2 = ans1;
  else {
    //ans2 += ans1;
    //ans2 = (ans2<=m*2)?ans2:m*2;
  }
  printf("%d %d",ans1,ans2);
  return 0;
}