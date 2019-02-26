#include<iostream>
//#define debug
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
          newNode->parent = p;
          p->left = newNode;
          break;
        }
      } else {
        if(p->right!=NULL) p = p->right;
        else {
          newNode->parent = p;
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
  TreeNode* tmp;
  if(node==NULL) return;
  else if(node->val==val) {
    tmp = node;
    node = NULL; 
    delete tmp;
  }
  else {
    TreeNode* p = node;
    TreeNode* tmp2;
    while(p!=NULL) {
      if(val<p->val) {
        if(p->left==NULL) return;
        else if(p->left->val!=val) p = p->left;
        else {
          #ifdef debug
          cout << "found at left\n";
          #endif
          tmp = p->left;
          if(tmp->left==NULL&&tmp->right==NULL) {
            p->left = NULL;
          } else if(tmp->left!=NULL&&tmp->right!=NULL) {
            #ifdef debug
            cout << "successor!\n";
            #endif
            tmp2 = successor(node, tmp);
            tmp2->left = tmp->left;
            tmp2->right = tmp->right;
            if(tmp2->parent!=NULL) {
              if(tmp2->parent->left==tmp2) tmp2->parent->left = NULL;
              else if(tmp2->parent->right==tmp2) tmp2->parent->right = NULL;
              tmp2->parent = NULL;
            }
            p->left = tmp2;
          } else {
            p->left = (tmp->left!=NULL) ? tmp->left:tmp->right; 
          }
          delete tmp;
          break;
        }
      } else {
        if(p->right==NULL) return;
        else if(p->right->val!=val) p = p->right;
        else {
          #ifdef debug
          cout << "found at right\n";
          #endif
          tmp = p->right;
          if(tmp->left==NULL&&tmp->right==NULL) {
            p->right = NULL;
          } else if(tmp->left!=NULL&&tmp->right!=NULL) {
            #ifdef debug
            cout << "successor!\n";
            #endif
            tmp2 = successor(node, tmp);
            tmp2->left = tmp->left;
            tmp2->right = tmp->right;
            if(tmp2->parent!=NULL) {
              if(tmp2->parent->left==tmp2) tmp2->parent->left = NULL;
              else if(tmp2->parent->right==tmp2) tmp2->parent->right = NULL;
              tmp2->parent = NULL;
            }
            p->right = tmp2;
          } else {
            p->right = (tmp->left!=NULL) ? tmp->left:tmp->right; 
          }
          delete tmp;
          break;
        }
      }
    }
    return;
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
      case 3: 
        #ifdef debug
        travel(tree,0);
        #endif
        del(tree, inp);
        break;
    }
  }
  #ifdef debug
  travel(tree,0);
  #endif
  return 0;
}