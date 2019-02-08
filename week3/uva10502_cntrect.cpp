#include<iostream>
using namespace std;
char tbl[101][101];
int num[101][101], sum[101][101];
void convert(int i, int j, char n) {
  num[i][j] = n - '0';
  sum[i][j] = num[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
}
int main(){
  int n, m;
  int tmp, ans=0;
  while (true) {
    cin >> n;
    if (n==0) break;
    cin >> m;
    ans = 0;
    for(int i=0;i<n;i++) cin >> tbl[i];
    for(int i=0;i<=n;i++)
      for(int j=0;j<=m;j++) {
        sum[i][j] = 0;
      }

    for(int i=0;i<n;i++) {
      for(int j=0;j<m;j++) {
        convert(i+1,j+1,tbl[i][j]);
      }
    }
    
    /*cout << "+++++"<<endl;
    for(int i=0;i<=n;i++) {
      for(int j=0;j<=m;j++) cout << sum[i][j] << " ";
      cout << endl;
    }
    cout << "-----"<<endl;*/
    for(int h=1;h<=n;h++) {
      for(int w=1;w<=m;w++) {
        //cout << w <<"x" << h <<"\n";
        for(int i=1;i+h-1<=n;i++) {
          for(int j=1;j+w-1<=m;j++) {
            //cout <<"\t("<<i<<","<<j<<")\t\t("<<i<<","<<j+w-1<<")"<<endl;
            //cout <<"\t("<<i+h-1<<","<<j<<")\t\t("<<i+h-1<<","<<j+w-1<<")"<<endl;
            tmp = sum[i+h-1][j+w-1] - sum[i+h-1][j-1] - sum[i-1][j+w-1] + sum[i-1][j-1];
            //cout << "i"<<i<<", j"<<j<<" "<<tmp<<endl;
            if (tmp==w*h) ans++;
          }
        }
      }
      //cout << endl;
    }
    cout << ans << endl;
  }
  return 0;
}