#include<cstdio>
#include<cstring>
#include<cmath>
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

bool stopDP = false;
bool visited[MAXN+1][MAXN+1];
int res[MAXN+1][2];
struct Coor{
  int first;
  int second;
  int drt;
};


Coor parent[2][MAXN+1][MAXN+1];
int dp[2][MAXN+1][MAXN+1];
int cnt[2][MAXN+1][MAXN+1];

Coor make_coor(int drt,int first,int second) {
  Coor tmp;
  tmp.first = first;
  tmp.second = second;
  tmp.drt = drt;
  return tmp;
}
void reset(bool all) {
  for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
      visited[i][j] = false;
      if(all) {
        parent[0][i][j] = make_coor(-1,-1,-1);
        parent[1][i][j] = make_coor(-1,-1,-1);
      }
    }
  }
}
Coor backtrack(int drt, int ei, int ej,int res);
bool bfs(int si, int sj, int drt, char (&map)[MAXN+1][MAXN+1]);
bool bfs(int sj, int sdrt) {
  return bfs(0, sj, sdrt, map); 
}
bool bfs(int si, int sj, int sdrt) {
  return bfs(si, sj, sdrt, map);
}
bool bfs(int sj, int sdrt, char (&map)[MAXN+1][MAXN+1]) {
  return bfs(0, sj, sdrt, map);
}
bool bfs(int si, int sj, int sdrt, char (&map)[MAXN+1][MAXN+1]){
  //drt: 1-forward 0-backward
  reset(false);
  //int drt = sdrt;
  #ifdef debug
  printf("--------- bfs(%d,%d,%d - %c) ------------\n",si,sj,sdrt,(sdrt)?'>':'<');
  #endif
  
  //layer[si][sj] = 0;
  parent[sdrt][si][sj] = make_coor(-1,-1,-1);
  Coor v;
  list< Coor > Q;
  Q.push_back(make_coor(sdrt,si,sj));
  while(!Q.empty()) {
    //pair< pair<int,int>, pair<int,int> > elm = Q.front();
    //pair<int,int> u = elm.first;
    Coor u = Q.front();
    Q.pop_front();
    
    if(stopDP) {
      switch(dp[u.drt][u.first][u.second]) {
        case 2:
          #ifdef debug
          printf("[DP] Woohoo! Treasure $$$ (from %d %d %c)\n",u.first,u.second,(u.drt)?'>':'<');
          #endif
          return true;
        case 1:
          #ifdef debug
          printf("[DP] FAILED! Tunnel XXX (from %d %d %c)\n",u.first,u.second,(u.drt)?'>':'<');
          #endif
          continue;
        default:break;
      }
    }

    #ifdef debug
    printf("now %c %d %d\t",(u.drt==1)?'>':'<',u.first,u.second);
    if(parent[u.drt][u.first][u.second].first!=-1 && parent[u.drt][u.first][u.second].second != -1)
      printf("\t- parent: %d %d",parent[u.drt][u.first][u.second].first,parent[u.drt][u.first][u.second].second);
    printf("\n");
    #endif
    
    visited[u.first][u.second] = true;
    vector< Coor > adj;
    switch(map[u.first][u.second]) {
      case '$': 
        #ifdef debug
        printf("Woohoo! Found the treasure: %d %d\n",u.first,u.second);
        #endif
        backtrack(u.drt,u.first,u.second,2);
        return true;
      case '@':
        #ifdef debug
        printf("FAILED! Found the tunnel: %d %d\n",u.first,u.second);
        #endif
        backtrack(u.drt,u.first,u.second,1);
        continue;
      case '.':
        if(u.first+1<n) adj.push_back(make_coor(u.drt,u.first+1, u.second));
      break;
      default:
        switch(u.drt) {
          case 0: //backward
            if(u.second-1>=0) adj.push_back(make_coor(u.drt,u.first, u.second-1));
            else {
              //drt = 1;
              //printf("Switch direction to %d at %d %d.\n",drt,u.first,u.second);
              adj.push_back(make_coor(1,u.first, u.second+1));
            }
          break;
          case 1: //forward
            if(u.second+1<m) adj.push_back(make_coor(u.drt,u.first, u.second+1));
            else {
              //drt = 0;
              //printf("Switch direction to %d at %d %d.\n",drt,u.first,u.second);
              adj.push_back(make_coor(0,u.first, u.second-1));
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
        
      //if(parent[v.drt][v.first][v.second].first==-1 || (parent[v.drt][v.first][v.second].first==u.first&&parent[v.drt][v.first][v.second].second==u.second)) {
        if(v.first<n) {
          //if(v.first!=si && v.second!=sj) {
            parent[v.drt][v.first][v.second].first = u.first;
            parent[v.drt][v.first][v.second].second = u.second;
            parent[v.drt][v.first][v.second].drt = u.drt;
          //}
          Q.push_back(v);
        }
      /*} else {
        printf("Cannot go %c to %d %d, its parent: %d %d, current: %d %d\n",(v.drt)?'>':'<',v.first,v.second,parent[v.drt][v.first][v.second].first,parent[v.drt][v.first][v.second].second,u.first,u.second);
      }*/
    }
    
  }
  return false;
}

Coor backtrack(int drt, int ei, int ej,int res,bool findAns);
Coor backtrack(int drt, int ei, int ej,int res) {
  return backtrack(drt,ei,ej,res,false);
} 
Coor backtrack(int drt, int ei, int ej,int res,bool findAns) {
  Coor tmp = parent[drt][ei][ej];
  int ni, nj, ndrt;
  int tick[2][MAXN+1][MAXN+1]={};

  if(res!=-1) {
    dp[drt][ei][ej]=res;
    cnt[drt][ei][ej]++;
    tick[drt][ei][ej]=1;
  }
  #ifdef debug
  printf("[BACK START]\n");
  printf("- %d %d(%c)",ei,ej,(drt)?'>':'<');
  if(ei+1<n && dp[drt][ei+1][ej]==2) printf("--candidate");
  printf("--cnt:%d",cnt[drt][ei][ej]);
  printf("\n");
  #endif
  while(tmp.first!=-1 && tmp.second!=-1) {
    ndrt = tmp.drt;ni = tmp.first; nj = tmp.second;
    
    #ifdef debug
    printf("- %d %d(%c)",ni,nj,(ndrt)?'>':'<');
    if(ni+1<n && dp[ndrt][ni+1][nj]==2) printf("--candidate");
    printf("--cnt:%d",cnt[ndrt][ni][nj]);
    printf("\n");
    #endif

    if(res!=-1) {
      dp[ndrt][ni][nj] = res;
      if(tick[ndrt][ni][nj]==0) {
        cnt[ndrt][ni][nj]++;
        tick[ndrt][ni][nj]=1;
      }
    } else if(findAns) {
      if(ni+1<n && bfs(ni+1,nj,ndrt)) return make_coor(ndrt,ni,nj); 
    }
    tmp = parent[tmp.drt][ni][nj];
  }
  #ifdef debug
  printf("\n");
  #endif
  return make_coor(-1,-1,-1);
}
void read_input() {
  scanf("%d %d",&m,&n);
  for(int i=0;i<n;i++) {
    scanf("%s",map[i]);
  }
}

int main() {
  read_input();
  reset(true);

  vector<int> tunnelPos;
  int tmp = 0;
  for(int j=0;j<m;j++) {
    tmp = 0;
    if(bfs(j,0)) {
      res[j][0]=1;
      tmp++;
    }
    if(bfs(j,1)) {
      res[j][1]=1;
      tmp++;
    }
    ans1 += tmp;
    
    if(map[n-1][j]=='@') tunnelPos.push_back(j);
  }

  int tunnelN = tunnelPos.size();

  #ifdef debug
  printf("\n");
  #endif

  ans2 = ans1;
  stopDP = true;
  
  Coor a,b;
  for(int i=0;i<tunnelN;i++) {
    a = backtrack(0, n-1, tunnelPos[i], -1, true);
    #ifdef debug
    printf("[BACK END] ");
    if(a.drt!=-1) {
      printf("drt: %d, coor: %d %d, cnt: %d",a.drt,a.first,a.second,cnt[a.drt][a.first][a.second]);
    }
    printf("\n");
    #endif
    b = backtrack(1, n-1, tunnelPos[i], -1, true);
    #ifdef debug
    printf("[BACK END] ");
    if(b.drt!=-1) {
      printf("drt: %d, coor: %d %d, cnt: %d",b.drt,b.first,b.second,cnt[b.drt][b.first][b.second]);
    }
    printf("\n");
    #endif
    if(a.drt!=-1 && b.drt!=-1 && a.first==b.first && a.second==b.second) {
      tmp = cnt[a.drt][a.first][a.second] + cnt[b.drt][b.first][b.second];
      if(ans1+tmp>ans2) ans2 = ans1+tmp;
    } else {
      if(a.drt!=-1) {
        tmp = cnt[a.drt][a.first][a.second];
        if(ans1+tmp>ans2) ans2 = ans1+tmp;
      }
      if(b.drt!=-1) {
        tmp = cnt[b.drt][b.first][b.second];
        if(ans1+tmp>ans2) ans2 = ans1+tmp;
      }
    }
  }
  
  if(ans2>m*2) ans2 = m*2;
  printf("%d %d",ans1,ans2); 
  return 0;
}