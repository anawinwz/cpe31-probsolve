#include<iostream>
#define debug
using namespace std;
typedef int ValType;
struct TreeNode {
  ValType val;
  TreeNode* left = NULL;
  TreeNode* right = NULL;
  TreeNode* parent = NULL;
  TreeNode(ValType val, TreeNode* left, TreeNode* right)
    : val(val), left(left), right(right) {}
};
TreeNode* insert(TreeNode*& node, int val) {
  TreeNode* newNode = new TreeNode(val, NULL, NULL);
  if(node==NULL) {
    node = newNode;
  } else {
    TreeNode* p = node;
    while(true) {
      if(val<p->val) {
        if(p->left!=NULL) p = p->left;
        else {
          newNode->parent = p;
          p->left = newNode;
          return newNode;
        }
      } else {
        if(p->right!=NULL) p = p->right;
        else {
          newNode->parent = p;
          p->right = newNode;
          return newNode;
        }
      }
    }
  }
}
TreeNode* searchNode(TreeNode*& node, int val) {
  if(node==NULL) return NULL;
  else {
    TreeNode* p = node;
    while(p!=NULL) {
      if(val==p->val) return p;
      else if(val<p->val) p = p->left;
      else p = p->right;
    }
    return NULL;
  }
}
int search(TreeNode*& node, int val) {
  if(searchNode(node,val)!=NULL) return 1;
  return 0;
}
TreeNode* successor(TreeNode*& root, TreeNode*& node) {
  TreeNode* p;
  if(node==NULL) return NULL;
  else if(node->right!=NULL) {
    #ifdef debug
    cout << "right is not null\n";
    #endif
    p = node->right;
    while(p->left!=NULL) {
      p = p->left; 
    }
    #ifdef debug
    cout << "return!\n"; 
    #endif
    return p;
  } else {
    #ifdef debug
    cout << "right is null\n";
    #endif
    TreeNode* succ; 
    p = root;
    while(p!=NULL) {
      if(node->val<p->val) {
        succ = p;
        p = p->left;
      } else if(node->val>p->val) {
        p = p->right;
      } else break;
    }
    return succ;
  }
}
void del(TreeNode*& node, int val) {
  TreeNode* todel = searchNode(node, val);
  if(todel==NULL) return;
  
  if(todel->left==NULL&&todel->right==NULL) {
    if(todel->parent==NULL) node = NULL;
    else {
      if(todel==todel->parent->left) todel->parent->left = NULL;
      else todel->parent->right = NULL;
    }
    delete todel;
  } else if(todel->left==NULL||todel->right==NULL) {
    TreeNode* child = (todel->left!=NULL) ? todel->left : todel->right;
    child->parent = todel->parent;
    if(todel->parent==NULL) node = child; 
    else {
      if(todel==todel->parent->left) todel->parent->left = child;
      else todel->parent->right = child;
    }
    delete todel;
  } else {
    TreeNode* succ = successor(node, todel);
    int tmp = succ->val;
    del(node, tmp);
    todel->val = tmp;
  }
}

#ifdef debug
void travel(TreeNode*& node, int level) {
  if(node==NULL) return;
  else {
    travel(node->right, level+1);
    for(int l=0;l<level;l++) cout << "...";
    cout << "* " << node->val << "\n";
    travel(node->left, level+1);
  }
}
#endif
bool inputInsert(TreeNode*& root) {
  if(root==NULL) return false;
  cout << "-----root: "<<root->val<<"\n";
  int l,r;
  cin >> l >> r;

  if(l!=-1) {
    root->left = new TreeNode(l, NULL, NULL);
    root->left->parent = root;
  }
  
  if(r!=-1) {
    root->right = new TreeNode(r, NULL, NULL);
    root->right->parent = root;
  }
  inputInsert(root->left);
  inputInsert(root->right);
  
  return true;
}
int main() {
  ios::sync_with_stdio(false);
  int rootval;
  while(true) {
    cin >> rootval;
    if(rootval==-1) break;
    TreeNode* tree = new TreeNode(rootval, NULL, NULL);
    inputInsert(tree);
    travel(tree, 0);
    cout << "--------------\n";
  }
  return 0;
}