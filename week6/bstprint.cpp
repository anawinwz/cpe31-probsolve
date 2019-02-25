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
void travel(TreeNode*& node, int level) {
  if(node==NULL) return;
  else {
    travel(node->right, level+1);
    for(int l=0;l<level;l++) cout << "...";
    cout << "* " << node->val << "\n";
    travel(node->left, level+1);
  }
}
TreeNode* tree = NULL;
int main() {
  ios::sync_with_stdio(false);
  int n, inp;
  cin >> n; 
  for(int nn=0;nn<n;nn++) {
    cin >> inp;
    insert(tree, inp);
  }
  travel(tree, 0);
  return 0;
}