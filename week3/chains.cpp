#include<iostream>
using namespace std;
struct Node {
  int data;
  int isEnd = 0;
  Node* prev = NULL;
  Node* next = NULL;
  Node* tail = NULL;
  Node* head = NULL;
  int isRev = 0;
  Node(int data)
    : data(data) {}
};

void tail_point(int mode, Node* header, Node* target) {
  Node* p = header;
  
  if (mode==0) {
    while (p->next!=NULL) {
      p = p->next;
    };
    p->next = NULL;
  } else {
    Node* tmp;
    while(true) {
      tmp = p->next;
      p->next = p->prev;
      p->prev = tmp;
      if(p->next != NULL) p = p->next;
      else break;
    }
    p->next = NULL;
  }
  p->isEnd = 0;

  if(target!=NULL) {
    target->prev = NULL;
    target->isEnd = 1;
  }
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
/*
void reverse_line(Node* header) {
  Node* tmp;
  Node* p = header;
  while(p!=NULL) {
    tmp = p->next;
    p->next = p->prev;
    p->prev = tmp;
    p = p->next;
  }
}
*/
void print_node(Node* node) {
  cout << "++++++++++++++++" <<endl;
  cout << "data : " <<node->data<<endl<<endl;
  
  cout << "isEnd : "<<node->isEnd<<", ";
  cout << "isRev : "<<node->isRev<<endl<<endl;
  cout << "prev : " <<((node->prev!=NULL)?node->prev->data:0)<<", ";
  cout << "next : " <<((node->next!=NULL)?node->next->data:0)<<endl;
  cout << "head : " <<((node->head!=NULL)?node->head->data:0)<<", ";
  cout << "tail : " <<((node->tail!=NULL)?node->tail->data:0)<<endl;
  cout << "++++++++++++++++" <<endl;

}
int main() {
  Node* node[100002];
  for (int i=1;i<=100000;i++) node[i] = new Node(i);
  for (int i=1;i<=100000;i++) {
    if (i>1) node[i]->prev = node[i-1];
    if (i<100000) node[i]->next = node[i+1];
  }

  int l, n, lastI=0, tmp;
  cin >> l >> n;
  for(int ll=0;ll<l;ll++) {
    cin >> tmp;
    if (lastI > 0){
      node[lastI]->next = NULL;
      node[lastI]->isEnd = 1;
    }
    
    if(lastI+1 <= 100000) {
      node[lastI+1]->prev = NULL;

      node[lastI+1]->isEnd = 1;
      
      node[lastI+1]->head = (lastI+1<=100000) ? node[lastI+1]:NULL;
      node[lastI+1]->tail = (lastI+tmp<=100000) ? node[lastI+tmp]:NULL;
    }
    if(lastI+tmp <= 100000) {
      node[lastI+tmp]->next = NULL;

      node[lastI+tmp]->isEnd = 1;
      
      node[lastI+tmp]->head = (lastI+1<=100000) ? node[lastI+1]:NULL;
      node[lastI+tmp]->tail = (lastI+tmp<=100000) ? node[lastI+tmp]:NULL;
    }
    lastI+=tmp;
  }

  Node* curr = node[1];
  Node* tmpp;
  Node* lastHead = NULL;
  char cmd; int at, mode;
  for(int nn=0;nn<n;nn++){
    cin >> cmd;

    cout << "--------------" <<endl;
    if(lastHead!=NULL) cout << "prev lastHead: " <<lastHead->data<<endl;
    if (lastHead == NULL || curr->tail!=NULL && curr->tail!=lastHead->tail) lastHead = curr;
    cout << "now lastHead: " <<lastHead->data<<endl;
    cout << "--------------" <<endl;

    switch(cmd) {
      case 'F':
        if(lastHead->isRev==0 && curr->next!=NULL) curr=curr->next;
        else if(lastHead->isRev==1 && curr->prev!=NULL) curr = curr->prev;
        break;
      case 'B':
        if(lastHead->isRev==0 && curr->prev!=NULL) curr=curr->prev;
        else if(lastHead->isRev==1 && curr->next!=NULL) curr = curr->next;
        break;
      case 'C':
        cin >> at;
       // cout << "try to combine " <<at<<endl;
        print_node(curr);
        if((lastHead->isRev==0 && curr->next!=NULL) || (lastHead->isRev==1 && curr->prev!=NULL)) {
          
          curr = (lastHead->isRev==0) ? curr->next : curr->prev;
          cout << "\tGo to "<<curr->data<<endl;
          
          tmpp = (lastHead->isRev==0) ? curr->prev : curr->next;

          if(curr->head==NULL || curr->data > curr->head->data) {
            curr->prev = NULL;
            curr->tail = curr;
            curr->head = curr;
          }
          print_node(curr);

          
          curr = tmpp;
          cout << "\tGo to "<<curr->data<<endl;
          
          if (lastHead->isRev==0) lastHead->tail = curr;
          else lastHead->head = curr;

          if (lastHead->isRev==0) tmpp->prev = NULL;
          else tmpp->next = NULL;
          tmpp->isEnd = 1;
        }


        if(node[at]->data > node[at]->head->data) {
          //This is reverse node.
          node[at]->isRev = 1;

          node[at]->next = curr;
          if(node[at]->tail!=NULL) {
            node[at]->tail->isEnd = 0;
            node[at]->tail->prev = (lastHead->isRev==0) ? curr->next : curr->prev;
          }
        } else {
          node[at]->prev = curr;
          if(node[at]->tail!=NULL) {
            node[at]->tail->isEnd = 0;
            node[at]->tail->next = (lastHead->isRev==0) ? curr->next : curr->prev;
          }
        }
        node[at]->isEnd = 0;
        
        tmpp = (lastHead->isRev==0) ? curr->next : curr->prev;
        if(tmpp!=NULL) {
          tmpp->prev = NULL;
          tmpp->isEnd = 1;
        }

        curr->isRev = lastHead->isRev;
        if(curr->isRev==0) curr->next = node[at];
        else curr->prev = node[at];
        print_node(curr);
        curr = node[at];
        break;
    }
    cout << "FINAL CURR: " << curr->data << endl;
    /*cout << "--------" << endl;
    print_list(node[1]);
    cout << endl << "--------" << endl;*/
  }
  return 0;
}