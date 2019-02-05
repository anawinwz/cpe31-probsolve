#include<iostream>
using namespace std;
struct Node {
  int data;
  int isEnd = 0;
  Node* prev = NULL;
  Node* next = NULL;
  Node(int data)
    : data(data) {}
};

void tail_point(Node* header, Node* target) {
  Node* p = header;
  while (p->next!=NULL) {
    p = p->next;
  }
  //cout << "found last " <<p->data<<endl;
  p->next = NULL;
  p->isEnd = 0;
  target->prev = NULL;
  target->isEnd = 1;
}
void print_list(Node* header) {
  Node* p = header;
  while (p!=NULL) {
    if (p->prev!=NULL) cout << " <- ";
    cout << p->data;
    if (p->next!=NULL) cout << " -> ";
    p = p->next;
  }
}
void reverse_line(Node* header) {
  Node* tmp;
  Node* p = header;
  while(p!=NULL) {
    //prev to next
    tmp = p->next;
    p->next = p->prev;
    p->prev = tmp;
    p = p->next;
  }
}
int main() {
  Node* node[100001];
  for (int i=1;i<=100000;i++) node[i] = new Node(i);
  for (int i=1;i<=100000;i++) {
    if (i>1) node[i]->prev = node[i-1];
    if (i<100000) node[i]->next = node[i+1];
  }

  int l, n, lastI=0, tmp;
  cin >> l >> n;
  node[1]->isEnd = 1;
  node[1]->prev = NULL;
  for(int ll=0;ll<l;ll++) {
    if (lastI > 0){
      node[lastI]->next = NULL;
      node[lastI]->isEnd = 1;

      node[lastI+1]->prev = NULL;
      node[lastI+1]->isEnd = 1;
    }
    cin >> tmp;
    //cout << "range ("<<lastI+1<<","<<lastI+tmp<<")"<<endl;
    node[lastI+tmp]->isEnd = 1;
    node[lastI+tmp]->next = NULL;
    lastI+=tmp;
  }

  Node* curr = node[1];
  Node* tmpp;
  char cmd; int at;
  for(int nn=0;nn<n;nn++){
    cin >> cmd;
    /*cout << "--------" << endl;
    print_list(node[1]);
    cout << endl << "--------" << endl;*/
    switch(cmd) {
      case 'F':
        if(curr->next!=NULL) curr=curr->next;
        break;
      case 'B':
        if(curr->prev!=NULL) curr=curr->prev;
        break;
      case 'C':
        cin >> at;
       // cout << "try to combine " <<at<<endl;
        if(curr->next!=NULL) curr=curr->next;

        tmpp = curr;
        curr = curr->prev;
        curr->isEnd = 1;
        
        tmpp->prev = NULL;
        tmpp->isEnd = 1;

        if (node[at]->next!=NULL || node[at]->prev==NULL) {
         // cout << "normal connect!" <<endl;
        } else {
          //cout << "reverse before connect!" <<endl;
          reverse_line(node[at]);
          //print_list(node[at]);
        }
        node[at]->prev = curr;
        node[at]->isEnd = 0;
        tail_point(node[at], curr->next);
        curr->next = node[at];
        curr = curr->next;
        break;
    }
    cout << curr->data << endl;
  }
  return 0;
}