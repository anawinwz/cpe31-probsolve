#include<iostream>
using namespace std;
typedef int ValType;
struct TreeNode {
  ValType val;
  TreeNode* left = NULL;
  TreeNode* right = NULL;
  TreeNode(ValType val, TreeNode* left, TreeNode* right)
    : val(val), left(left), right(right) {}
};
void insert(TreeNode*& node, int val) {
  TreeNode* newNode = new TreeNode(val, NULL, NULL);
  if(node==NULL) {
    node = newNode;
  } else {
    TreeNode* p = node;
    while(true) {
      if(val<p->val) {
        if(p->left!=NULL) p = p->left;
        else {
          p->left = newNode;
          break;
        }
      } else {
        if(p->right!=NULL) p = p->right;
        else {
          p->right = newNode;
          break;
        }
      }
    }
  }
}
int search(TreeNode*& node, int val) {
  if(node==NULL) return false;
  else {
    TreeNode* p = node;
    while(p!=NULL) {
      if(val==p->val) return 1;
      else if(val<p->val) p = p->left;
      else p = p->right;
    }
    return 0;
  }
}
TreeNode* tree = NULL;
int main() {
  ios::sync_with_stdio(false);
  int m, k, inp;
  cin >> m; 
  for(int mm=0;mm<m;mm++) {
    cin >> k >> inp;
    switch(k){
      case 1: insert(tree, inp);break;
      case 2: cout << search(tree, inp) << "\n";break;
    }
  }
  return 0;
}