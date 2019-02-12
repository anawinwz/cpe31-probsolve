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
pair<int,int> parent[MAXN+1][MAXN+1];

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
  printf("--------- bfs(%d,%d,%d - %c) ------------\n",si,sj,drt,(drt)?'>':'<');
  #endif

  if(isCnt) {
    for(int i=0;i<n;i++) {
      for(int j=0;j<m;j++) {
        visited[i][j] = false;
        parent[i][j] = make_pair(-1,-1);
      }
    }
  }
  
  //layer[si][sj] = 0;
  parent[si][sj] = make_pair(si,sj);
  pair<int,int> v;
  list< pair< pair<int,int>, pair<int,int> > > Q;
  Q.push_back(make_pair(make_pair(si,sj),make_pair(-1,-1)));
  while(!Q.empty()) {
    pair< pair<int,int>, pair<int,int> > elm = Q.front();
    pair<int,int> u = elm.first;
    Q.pop_front();

    #ifdef debug
    printf("now %d %d\t",u.first,u.second);
    if(elm.second.first!=-1) printf(" (skipped %d,%d)",elm.second.first, elm.second.second);
    printf("\n");
    #endif

    visited[u.first][u.second] = true;
    vector< pair<int,int> > adj;
    switch(map[u.first][u.second]) {
      case '$': 
        #ifdef debug
        printf("Woohoo! Found treasure! %d %d\n",u.first,u.second);
        #endif
        return true;
      case '@':
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
        
      //if(parent[v.first][v.second].first==-1) {
        parent[v.first][v.second].first = u.first;
        parent[v.first][v.second].second = u.second;
        if(v.first<n) {
          Q.push_back(make_pair(make_pair(v.first, v.second), elm.second));
        }
      /*} else {
        printf("Cannot go to %d %d, its parent: %d %d, current: %d %d\n",v.first,v.second,parent[v.first][v.second].first,parent[v.first][v.second].second,u.first,u.second);
      }*/
    }
    
  }
  return false;
}

void read_input() {
  scanf("%d %d",&m,&n);
  for(int i=0;i<n;i++) {
    scanf("%s",map[i]);
  }
}

int main() {
  read_input();
  for(int j=0;j<m;j++) {
    if(bfs(j,0)) ans1++;
    if(bfs(j,1)) ans1++;
  }
  
  if(n==1) ans2 = ans1;
  printf("%d %d",ans1,ans1);
  return 0;
}