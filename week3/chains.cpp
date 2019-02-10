#include<stdio.h>
#include<iostream>
using namespace std;
//#define debug TRUE
#define gc getchar_unlocked
void scan_integer( int &x )
{
    register int c = gc();
    x = 0;
    int neg = 0;
    for( ; ((c<48 || c>57) && c != '-'); c = gc() );
    if( c=='-' ) {
        neg=1;
        c=gc();
    }
    for( ;c>47 && c<58; c = gc() ) {
        x = (x << 1) + (x << 3) + c - 48;
    }
    if( neg )
        x=-x;
} 

struct Node {
  int data;
  int head;
  int tail;
  Node* prev = NULL;
  Node* next = NULL;
  Node(int data)
    : data(data) {}
};
void print_list(Node* header) {
  Node* p = header;
  //int isRev = (p->isRev==1 || (p->next==NULL && p->prev!=NULL)) ? 1 : 0;
  while (p!=NULL) {
    if (p->prev!=NULL) cout << " <- ";
    cout << p->data;
    if (p->next!=NULL) cout << " -> ";
    
    p = p->next;
  }
}
Node* node[100002];
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
void reverse_node(Node* header) {
  #ifdef debug
    cout << "Reverse Node : "<<header->data<<endl;
  #endif
  Node* p = header;
  Node* tmp = p->next;
  p->next = p->prev;
  p->prev = tmp;
}
void updateLast(Node*& curr, int& lastHead, int& lastTail) {
  if(curr->head!=0) {
    if(curr->head!=lastHead) {
      lastHead = curr->head;
      #ifdef debug
      cout <<"lastHead is changed to "<<lastHead<<endl;
      #endif
    }
  }
  if(curr->tail!=0) {
    if(curr->tail!=lastTail) {
      lastTail = curr->tail;
      #ifdef debug
      cout <<"lastTail is changed to "<<lastTail<<endl;
      #endif 
    }
  }
}
int main() {
  for (int i=1;i<=100000;i++) node[i] = new Node(i);
  for (int i=1;i<=100000;i++) {
    node[i]->head = 0;
    node[i]->tail = 0;
    if (i>1) node[i]->prev = node[i-1];
    if (i<100000) node[i]->next = node[i+1];
  }

  int l, n, lastI=0, tmp;
  //scanf("%d %d",&l,&n);
  scan_integer(l);
  scan_integer(n);
  for(int ll=0;ll<l;ll++) {
    //scanf("%d",&tmp);
    scan_integer(tmp); 

    node[lastI+1]->prev = NULL;
    node[lastI+1]->head = 0;
    node[lastI+1]->tail = lastI+tmp;
    //node[lastI+1]->isEnd = 1;

    node[lastI+tmp]->next = NULL;
    node[lastI+tmp]->head = 0;
    node[lastI+tmp]->tail = lastI+tmp;
    //node[lastI+tmp]->isEnd = 1;

    lastI+=tmp;
  }

  Node* curr = node[1];
  curr->head = 1;
  Node* tmpp;
  int lastHead = curr->head;
  int lastTail = curr->tail;
  char cmd; int at;//, mode;
  for(int nn=0;nn<n;nn++){
    scanf(" %c",&cmd);
    /*cout << "--------" << endl;
    print_list(node[1]);
    cout << endl << "--------" << endl;*/
    updateLast(curr, lastHead, lastTail);
    if (curr->head==0) curr->head = lastHead;
    switch(cmd) {
      case 'F':
        if(curr->next!=NULL) {
          if(curr->next!=NULL && curr->next->next==curr) reverse_node(curr->next);
          curr=curr->next;
        }
        break;
      case 'B':
        if(curr->prev!=NULL) {
          //if(curr->next!=NULL && curr->prev->next==curr) reverse_node(curr->prev);
          curr=curr->prev;
        }
        break;
      case 'C':
        //scanf("%d",&at);
        scan_integer(at);
       // cout << "try to combine " <<at<<endl;
        if(curr->next!=NULL) {
          if(curr->next->next==curr) reverse_node(curr->next);
          //curr = curr->next;

          tmpp = curr->next;
          //curr = curr->prev;

          /*
            curr - Last node before the unchained
            tmpp - Unchained head node
            <[curr]> ---X-CUT-X--- <[tmpp]> <[...]> <[...]
              ^                       ^
            new tail               new head of old tail
          */
          node[lastTail]->head = tmpp->data;
          
          tmpp->prev = NULL;
          tmpp->head = tmpp->data;
          tmpp->tail = lastTail;

          lastTail = curr->data;
          node[lastHead]->tail = lastTail;
          curr->tail = lastTail;

          updateLast(curr, lastHead, lastTail);
          #ifdef debug
          cout << "curr is " <<curr->data<< ", tmpp is "<<tmpp->data<<endl;
          #endif
      
          #ifdef debug
          printf("[%d] head: %d\ttail: %d\n",tmpp->data,tmpp->head,tmpp->tail);
          printf("[%d] head: %d\ttail: %d\n",tmpp->tail,node[tmpp->tail]->head,node[tmpp->tail]->tail);
          #endif
        }

        if (node[at]->next!=NULL || node[at]->prev==NULL) {
         // cout << "normal connect!" <<endl;
          
        } else {
          #ifdef debug
          cout << "Need to reverse first! Node: " << at <<endl;
          #endif
          //reverse_line(node[at]);
          reverse_node(node[at]);
        }
        
        if(curr->next!=NULL) {
          curr->next->prev = NULL;
        }            
        
        node[at]->head = lastHead;
        node[node[at]->tail]->head = lastHead;
        node[lastHead]->tail = node[at]->tail;
        node[at]->prev = curr;    

        curr->next = node[at]; 
        curr = curr->next;
        updateLast(curr, lastHead, lastTail);
        break;
    }
  
    //cout << ""<< curr->data << endl;
    #ifdef debug
    //print_list(node[1]);
    printf("\n");
    #endif
    printf("%d\n",curr->data);
  }
  return 0;
}