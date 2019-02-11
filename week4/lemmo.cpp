#include<cstdio>
#include<cstring>
#include<list>
#include<vector>
#include<utility>
#define MAXN 120
using namespace std;
vector< pair<int,int> > flrlist;
char map[MAXN+1][MAXN+1];

int qua2 = 0, qua1 = 0;

int n, m;

bool visited[MAXN+1][MAXN+1];
bool realVisited[MAXN+1][MAXN+1];
//int visitCnt[MAXN+1][MAXN+1];
int layer[MAXN+1][MAXN+1];

bool bfs(int si, int sj, char drt, bool isCnt, char (&map)[MAXN+1][MAXN+1]);
bool bfs(int sj, char drt) {
  return bfs(0, sj, drt, true, map); 
}
bool bfs(int sj, char drt, bool isCnt, char (&map)[MAXN+1][MAXN+1]) {
  return bfs(0, sj, drt, isCnt, map);
}
bool bfs(int si, int sj, char drt, bool isCnt, char (&map)[MAXN+1][MAXN+1]){
  //printf("--------- bfs(%d,%d,'%c') ------------\n",si,sj,drt);
  if(isCnt) {
    for(int i=0;i<n;i++) {
      for(int j=0;j<m;j++) {
        visited[i][j] = false;
        layer[i][j] = -1;
      }
    }
  }
  layer[si][sj] = 0;
  list< pair<int,int> > Q;
  Q.push_back(make_pair(si,sj));
  while(!Q.empty()) {
    pair<int,int> u = Q.front(), v;
    Q.pop_front();
    //if(visited[u.first][u.second]) {
      //printf("already visited %d %d\n",u.first,u.second);
      //continue;
    //}

    //printf("now %d %d\n",u.first, u.second);
    /*if (map[u.first][u.second]=='$') {
      //printf("found treasure at %d %d!\n",u.first,u.second);
      return true;
    } else if(map[u.first][u.second]=='@') {
      //printf("end tube at %d %d!\n",u.first,u.second);
      continue;
    }*/
    if(isCnt && !realVisited[u.first][u.second] && u.first<n-1 && map[u.first][u.second]=='#') {
      //printf("not visited %d %d\n",u.first,u.second);
      flrlist.push_back(make_pair(u.first, u.second));
    }

    visited[u.first][u.second] = true;
    realVisited[u.first][u.second] = true;
    vector< pair<int,int> > adj;
    switch(map[u.first][u.second]) {
      case '$': return true;
      case '@': continue;
      case '.':
        if(u.first+1<=n) adj.push_back(make_pair(u.first+1, u.second));
      break;
      default:
        
        switch(drt) {
          case '<': 
            if(u.second-1>=0) adj.push_back(make_pair(u.first, u.second-1));
            else {
              drt = '>';
              //printf("change direction to %c at %d %d\n",drt,u.first,u.second);
              adj.push_back(make_pair(u.first, u.second+1));
            }
          break;
          case '>': 
            if(u.second+1<m) adj.push_back(make_pair(u.first, u.second+1));
            else {
              drt = '<';
              //printf("change direction to %c at %d %d\n",drt,u.first,u.second);
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
      if(v.first<=n) {
        layer[v.first][v.second]=layer[u.first][u.second]+1;
        Q.push_back(make_pair(v.first, v.second));
      } 
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
  int ans=0, maxAns=0;
  for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
      realVisited[i][j]=false;
    }
  }
  for(int j=0;j<m;j++) {
    if(bfs(j,'<')) ans++;
    if(bfs(j,'>')) ans++;
  }
  //char newmap[MAXN+1][MAXN+1];
  //for(int i=0;i<n;i++) strcpy(newmap[i],map[i]);
  
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
      /*if(bfs(i,j,'<',false,map) || bfs(i,j,'>',false,map)) {
        printf("%d %d WORKS!\n",i,j);
      }*/
     // printf("after disable %d %d: %d\n",i,j,thisans);
      if(thisans>maxAns) maxAns = thisans;
      map[i][j]='#';
    }
  }
  printf("%d %d",ans,maxAns);
  return 0;
}