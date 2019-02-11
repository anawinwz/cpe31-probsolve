#include<cstdio>
#include<list>
#include<vector>
#include<utility>
//#define debug TRUE
#define MAXN 30
using namespace std;
char map[MAXN+1][MAXN+1];

int ans = 0;

int n, m;

bool visited[MAXN+1][MAXN+1];
int layer[MAXN+1][MAXN+1];

void bfs(int sj){
  #ifdef debug
  printf("--------- bfs(%d,%d) ------------\n",0,sj);
  #endif
  for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
      visited[i][j] = false;
      layer[i][j] = -1;
    }
  }
  layer[0][sj] = 0;
  list< pair<int,int> > Q;
  Q.push_back(make_pair(0,sj));
  while(!Q.empty()) {
    if(ans==1) return;

    pair<int,int> u = Q.front(), v;
    Q.pop_front();
    if(visited[u.first][u.second]) {
      //printf("already visited %d %d\n",u.first,u.second);
      continue;
    }
    visited[u.first][u.second] = true;
    
    #ifdef debug
    printf("now |(%d,%d)\t(%d,%d)|\n",u.first, u.second, u.first, u.second+1);
    #endif
    if(u.first==n-1) {
      if(map[u.first][u.second]!='#' && map[u.first][u.second+1]!='#') {
        ans = 1;
        #ifdef debug
        printf("can out at |(%d,%d)\t(%d,%d)|!\n",u.first,u.second,u.first,u.second+1);
        #endif
        return;
      }
    }
    //printf("\n");
    vector< pair<int,int> > adj;
    if(u.first-2>=0) adj.push_back(make_pair(u.first-1, u.second));
    if(u.first+2<=n) adj.push_back(make_pair(u.first+1, u.second));
    if(u.second-2>=0) adj.push_back(make_pair(u.first, u.second-1));
    if(u.second+2<m) adj.push_back(make_pair(u.first, u.second+1));
    int deg = adj.size();
    for(int i=0;i<deg;i++) {
      v = adj[i];
      if(map[v.first][v.second]=='#' || map[v.first][v.second+1]=='#') continue;
      if(v.first>0 && (map[v.first-1][v.second]=='#' || map[v.first-1][v.second+1]=='#')) {
        #ifdef debug
        printf("\ncollision\n|(%d,%d)\t(%d,%d)|\n|(%d,%d)\t(%d,%d)|\n\n",v.first-1,v.second,v.first-1,v.second+1,v.first,v.second,v.first,v.second+1);
        #endif
        continue;
      }

      //if(layer[v.first][v.second]==-1) {
        layer[v.first][v.second]=layer[u.first][u.second]+1;
        Q.push_back(make_pair(v.first, v.second));
      //}
      
    }
    
  }
  
}

void read_input() {
  scanf("%d %d",&n,&m);
  for(int i=0;i<n;i++) {
    scanf("%s",&map[i]);
  }
}

int main() {
  read_input();
  for(int j=0;j<m-1;j++) {
    if(ans==0 && map[0][j]!='#') bfs(j);
    if(ans==1) break;
  }
  if(ans==1) printf("yes");
  else printf("no");
  
  return 0;
}