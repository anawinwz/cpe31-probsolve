#include<cstdio>
#include<list>
#include<vector>
#include<utility>
#define MAXN 30
using namespace std;
char map[MAXN+1][MAXN+1];

int qua2 = 0, qua1 = 0;

int n, m;

bool visited[MAXN+1][MAXN+1];
int layer[MAXN+1][MAXN+1];

void bfs(int si, int sj){
  //printf("--------- bfs(%d,%d) ------------\n",si,sj);
  int tree = 0, rock = 0;
  for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
      visited[i][j] = false;
      layer[i][j] = -1;
    }
  }
  layer[si][sj] = 0;
  list< pair<int,int> > Q;
  Q.push_back(make_pair(si,sj));
  while(!Q.empty()) {
    pair<int,int> u = Q.front(), v;
    Q.pop_front();
    if(visited[u.first][u.second]) {
      //printf("already visited %d %d\n",u.first,u.second);
      continue;
    }
    visited[u.first][u.second] = true;
    //printf("now %d %d",u.first, u.second);
    switch(map[u.first][u.second]) {
      case '*':
        tree++;
        //printf(" - tree (*)");
        break;
      case '$':
        rock++;
        //printf(" - rock (#)");
        break;
    }
    //printf("\n");
    vector< pair<int,int> > adj;
    if(u.first-1>=0) adj.push_back(make_pair(u.first-1, u.second));
    if(u.first+1<n) adj.push_back(make_pair(u.first+1, u.second));
    if(u.second-1>=0) adj.push_back(make_pair(u.first, u.second-1));
    if(u.second+1<m) adj.push_back(make_pair(u.first, u.second+1));
    int deg = adj.size();
    for(int i=0;i<deg;i++) {
      v = adj[i];
      if(map[v.first][v.second]!='#') {
        
        //if(layer[v.first][v.second]==-1) {
          layer[v.first][v.second]=layer[u.first][u.second]+1;
          Q.push_back(make_pair(v.first, v.second));
        //}
      }
    }
    
  }
  if(tree>0 && rock>0) qua2++;
  else if(tree>0 || rock>0) qua1++; 
  //printf("===== Tree: %d / Rock: %d =====\n",tree,rock);
}

void read_input() {
  scanf("%d %d",&n,&m);
  for(int i=0;i<n;i++) {
    scanf("%s",&map[i]);
  }
}

int main() {
  read_input();
  for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
      if(map[i][j]!='#') bfs(i,j);
    }
  }
  printf("%d %d",qua2,qua1);
  return 0;
}