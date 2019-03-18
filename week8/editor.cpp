#include<iostream>
#include<vector>
#include<string>
using namespace std;
void printVec(vector<string> ed) {
  //cout << "\t";
  int size = ed.size();
  for(int i=0;i<size;i++) {
    cout << ed[i];
    if(i!=size-1) cout << " ";
  }
}
int main() {
  int n;
  vector<string> editor;
  
  int cursor = 0;
  string inp;
  
  ios::sync_with_stdio(false);
  cin >> n;

  char cmd;
  for(int nn=0;nn<n;nn++) {
    cin >> cmd;
    switch(cmd) {
      case 'i':
        cin >> inp;
        editor.insert(editor.begin()+cursor++, inp);
        break;
      case 'l':
        if (cursor>0) cursor--;
        break;
      case 'r':
        if (cursor<editor.size()) cursor++;
        break;
      case 'b':
        if (cursor>0) {
          editor.erase(editor.begin()+cursor-1);
          cursor--;
        }
        break;
      case 'd':
        if (cursor<editor.size()) {
          editor.erase(editor.begin()+cursor+1);
        }
        break;
    }
    //cout << "\tcursor: "<<cursor<<" ";
    //printVec(editor);
    //cout << "\n";
  }
  printVec(editor);
  return 0;
}