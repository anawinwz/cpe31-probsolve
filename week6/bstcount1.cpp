#include<cstdio>
//#define debug
#define REALMIN -1000000001
using namespace std;
typedef int ValType;
ValType minn = REALMIN, maxx = 0;
struct TreeNode {
  ValType val;
  TreeNode* left = NULL;
  TreeNode* right = NULL;
  TreeNode* parent = NULL;
  int size = 1;
  int min = REALMIN;
  int max = 0;
  TreeNode(ValType val, TreeNode* left, TreeNode* right)
    : val(val), left(left), right(right) {}
};
void insert(TreeNode*& node, int val) {
  TreeNode* newNode = new TreeNode(val, NULL, NULL);
  newNode->min = newNode->max = val;
  if(node==NULL) {
    node = newNode;
  } else {
    TreeNode* p = node;
    while(true) {
      p->size++;
      if(p->min==REALMIN||val<p->min) p->min = val;
      if(val>p->max) p->max = val;

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
TreeNode* searchNode(TreeNode*& node, int val) {
  if(node==NULL) return NULL;
  else {
    TreeNode* p = node;
    while(p->left!=NULL) {
      if(val==p->val) return p;
      else if(val<p->val&&p->left!=NULL) p = p->left;
      else if(val>=p->val&&p->right!=NULL) p = p->right;
      else break;
    }
    return p;
  }
}
int search(TreeNode*& node, int val) {
  if(searchNode(node,val)!=NULL) return 1;
  return 0;
}
#ifdef debug
void travel(TreeNode*& node, int level) {
  if(node==NULL) return;
  else {
    travel(node->right, level+1);
    for(int l=0;l<level;l++) printf("...");
    printf("* %d(size:%d)\n",node->val,node->size);
    travel(node->left, level+1);
  }
}
#endif
int count(TreeNode*& node, int find, int ans) {
  if(node==NULL) return ans;
  else if(find<node->min) return ans + node->size;
  else if(find>=node->max) return ans;
  else {
    if(find<node->val) ans = count(node->left, find, ans);

    //printf("* %d size: %d \n",node->val,node->size);
    if(node->val > find) ans++;

    if(find>node->val) ans = count(node->right, find, ans);
    else if(node->right!=NULL) ans += node->right->size;
    return ans;
  }
}
int findAns(TreeNode*& node, int val) {
  if(node==NULL) return 0;

  return count(node, val, 0);
}
TreeNode* tree = NULL;
int main() {
  int m, k, inp;
  scanf("%d",&m); 
  for(int mm=0;mm<m;mm++) {
    scanf("%d %d",&k,&inp);
    #ifdef debug
    if(k==1) {
      printf("\n---%d %d----\n",k,inp); 
      travel(tree,0);
      printf("----%d %d----\n",minn,maxx);
    }
    #endif
    switch(k){
      case 1: 
        insert(tree, inp);
        break;
      case 2: printf("%d\n", findAns(tree, inp));break;
    }
  }
  #ifdef debug
  //travel(tree,0);
  #endif
  return 0;
}