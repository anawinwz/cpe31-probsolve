#include<iostream>
using namespace std;
struct Node {
  int data;
  int isRev = 0;
  Node* prev = NULL;
  Node* next = NULL;
  Node* head = NULL;
  Node* tail = NULL;
  Node(int data)
    : data(data) {}
};
/*
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
}*/
void print_list(Node* header) {
  Node* p = header;
  int isRev = (p->isRev==1 || (p->next==NULL && p->prev!=NULL)) ? 1 : 0;
  while (p!=NULL) {
    if (isRev==0 && p->prev!=NULL) cout << " <- ";
    if (isRev==1 && p->next!=NULL) cout << " <- ";
    cout << p->data;
    if (isRev==0 && p->next!=NULL) cout << " -> ";
    if (isRev==1 && p->prev!=NULL) cout << " -> ";
    
    if(isRev==0) p = p->next;
    else if(isRev==1) p = p->prev;
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

    node[lastI+1]->prev = NULL;
    node[lastI+1]->head = node[lastI+1];
    node[lastI+1]->tail = node[lastI+tmp];
    //node[lastI+1]->isEnd = 1;

    node[lastI+tmp]->next = NULL;
    node[lastI+tmp]->head = node[lastI+1];
    node[lastI+tmp]->tail = node[lastI+tmp];
    //node[lastI+tmp]->isEnd = 1;

    lastI+=tmp;
  }

  Node* curr = node[1];
  Node* tmpp;
  int lastRev = 0;
  Node*& lastHead = curr->head;
  Node*& lastTail = curr->tail;
  char cmd; int at, mode;
  for(int nn=0;nn<n;nn++){
    cin >> cmd;
    /*cout << "--------" << endl;
    print_list(node[1]);
    cout << endl << "--------" << endl;*/
    if(((curr->head!=NULL&&curr==curr->head)||(curr->tail!=NULL&&curr==curr->tail)) && curr->isRev!=lastRev) {
      //cout <<"lastRev is changed to " << curr->isRev << endl;
      lastRev = curr->isRev;
    }
    if(curr->head!=NULL) {
      if(curr->head!=lastHead) {
        lastHead = curr->head;
        //cout <<"lastHead is changed to "<<lastHead->data<<endl; 
      }
    }
    if(curr->tail!=NULL) {
      if(curr->tail!=lastTail) {
        lastTail = curr->tail;
        //cout <<"lastTail is changed to "<<lastTail->data<<endl; 
      }
    }
    switch(cmd) {
      case 'F':
        if(lastRev == 0 && curr->next!=NULL) curr=curr->next;
        else if(lastRev == 1 && curr->prev!=NULL) curr=curr->prev;
        break;
      case 'B':
        if(lastRev == 0 && curr->prev!=NULL) curr=curr->prev;
        else if(lastRev == 1 && curr->next!=NULL) curr=curr->next;
        break;
      case 'C':
        cin >> at;
       // cout << "try to combine " <<at<<endl;
        if(lastRev == 0 && curr->next!=NULL) {

          curr = curr->next;
          tmpp = curr;
          curr = curr->prev;

          //Last node before the unchained
          //curr->isEnd = 1;
          
          //Unchained head node         
          tmpp->prev = NULL;
          //tmpp->isEnd = 1;
        } else if(lastRev == 1 && curr->prev!=NULL) {
          curr = curr->prev;
          tmpp = curr;
          curr = curr->next;

          //Last node before the unchained
          curr->head = curr;
          //curr->isEnd = 1;
          
          //Unchained head node
          tmpp->next = NULL;
          //tmpp->isEnd = 1;
        }

        if (node[at]->isRev==1 || (node[at]->next==NULL && node[at]->prev!=NULL)) {
          //cout << "this is reverse!" <<endl;
          //reverse_line(node[at]);
          mode = 1;
          //print_list(node[at]);
        } else {
         // cout << "normal connect!" <<endl;
          mode = 0;
        }
        
        //
        //tail_point(mode, node[at], curr->next);
            
        /*cout << "++++++++" << endl;
        print_list(node[at]);
        cout << endl << "++++++++" << endl;*/
        if (mode==0) {
          if(node[at]->isRev==1) {
            node[at]->head->tail = node[at]->head;
            node[at]->head->head = node[at];
            node[at]->head->isRev = 0;

            tmpp = node[at]->head;
            node[at]->head = node[at];
            node[at]->tail = tmpp;
            /*cout << "Swapping head and tail to NORMAL!" << endl;
            print_list(node[at]);
            cout << endl;*/
          }
          node[at]->prev = curr;
          node[at]->tail->next = NULL;

        } else {
          
          if(node[at]->isRev==0) {
            //node[at] becomes head
            node[at]->head->tail = node[at]->head;
            node[at]->head->head = node[at];
            node[at]->head->isRev = 1;

            tmpp = node[at]->head;
            node[at]->head = node[at];
            node[at]->tail = tmpp;
            /*cout << "Swapping head and tail to REVERSE!" << endl;
            print_list(node[at]);
            cout << endl;*/
          }
          node[at]->next = curr;
          node[at]->tail->prev = NULL;
        }
        
        
        //node[at]->isEnd = 0;
        node[at]->isRev = mode;
        curr->isRev = lastRev;

        if(lastRev==0) curr->next = node[at]; 
        else if (lastRev==1) curr->prev = node[at];

        if(lastRev==0) curr = curr->next;
        else if(lastRev==1) curr = curr->prev;
        break;
    }
    //cout << "--------" << endl;
    //print_list(node[1]);
    //cout << endl << "--------" << endl;
  
    cout << ""<< curr->data << endl;
  }
  return 0;
}