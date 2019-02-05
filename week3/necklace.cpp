#include<iostream>
using namespace std;
struct Node {
  int data;
  Node* next = NULL;
  Node(int data, Node* next)
    : data(data), next(next) {}
};
void tail_point(Node* header, Node* target) {
  Node* p = header;
  while (p->next!=NULL) {
    p = p->next;
  }
  p->next = target;
}
int nodeSize[300000];
int tour(Node* header) {
  if (nodeSize[header->data-1]) return nodeSize[header->data-1];
  if (header->next==NULL) nodeSize[header->data-1] = 1;
  else nodeSize[header->data-1] = 1+tour(header->next);
  return nodeSize[header->data-1];
}
void print_list(Node* header) {
  Node* p = header;
  while (p!=NULL) {
    cout << p->data << " ";
    p = p->next;
  }
}
int main() {
  Node* node[300000];
  //Node* tmp;
  int n;
  cin >> n;
  int x, y, maxx;
  for (int i=0;i<n;i++) node[i] = new Node(i+1, NULL);
  for (int i=0;i<n-1;i++) {
    cin >> x >> y;
    //cout << "hello " << node[x-1]->data << " " << node[y-1]->data<<endl; 
    //7(x) inserts after 4(y)
    tail_point(node[x-1],node[y-1]->next);
    node[y-1]->next = node[x-1];
  }
  for(int i=0;i<n;i++) {
    if(tour(node[i])==n) {
      print_list(node[i]);
      break;
    }
  }
  return 0;
}