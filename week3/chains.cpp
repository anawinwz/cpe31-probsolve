#include<stdio.h>
#include<iostream>
//#define debug TRUE
using namespace std;

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
Node* node[100002];
class Stack {
  private:
    Node* header = NULL;
    Node* tail = NULL;
  public:
    int isRev;
    bool is_empty();
    Node* top();
    Node* bottom();
    void push_list(Node*& list);
    Node* remove();
    Node* pop();
};
bool Stack::is_empty() {
  return (header==NULL);
}
Node* Stack::top() {
  return header;
}
Node* Stack::bottom() {
  return tail;
}
void Stack::push_list(Node*& list) {
  #ifdef debug
    cout << "Push list!!"<<endl;
    cout << "Push list: "<<list->data<<" "<<list->head<<endl;
  #endif

  int tmp = list->head;
  list->head = list->tail;
  list->tail = tmp;

  if(list->tail!=0) {
    node[list->tail]->head = list->data;
    node[list->tail]->tail = list->tail; 
  }
  
  if (tail==NULL) {
    header = list;
  } else {
    tail->prev = list;
  }
  if(list->tail!=0) tail = node[list->tail];
}
Node* Stack::remove() {
  #ifdef debug
    cout << "Try to REMOVE stack!"<<endl;
  #endif
  if(header==NULL) return NULL;

  #ifdef debug
    cout << "[REMOVE] Header is "<<header->data<<endl;
  #endif

  Node* tmp = header;
  header = NULL;
  tail = NULL;
  return tmp;
}
Node* Stack::pop() {
  #ifdef debug
    cout << "Try to POP stack!"<<endl;
  #endif
  if(header==NULL) return NULL;

  #ifdef debug
    cout << "[POP] Header is "<<header->data<<endl;
  #endif

  //Reverse before POP
  Node* tmp = header->next;
  header->next = header->prev;
  header->prev = tmp;
  #ifdef debug
    cout << "Reverse Success!" <<endl;
  #endif

  tmp = header;
  if(header->next!=NULL) {
    header->next->head = header->head;
    header->next->tail = header->tail;
    if(tail!=NULL) {
      tail->head = header->head;
      tail->tail = header->tail;
    } 
  }
  header = header->next;
  if(header==NULL) tail = NULL;
  return tmp;
}
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
void updateLast(Node*& curr, int& lastHead, int& lastTail) {
  /*curr->head = lastHead;
  curr->tail = lastTail;
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
  }*/
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
    node[lastI+1]->head = lastI+1;
    node[lastI+1]->tail = lastI+tmp;
    //node[lastI+1]->isEnd = 1;

    node[lastI+tmp]->next = NULL;
    node[lastI+tmp]->head = lastI+1;
    node[lastI+tmp]->tail = lastI+tmp;
    //node[lastI+tmp]->isEnd = 1;

    lastI+=tmp;
  }

  Stack rev;
  rev.isRev = 1;
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
    //updateLast(curr, lastHead, lastTail);
    switch(cmd) {
      case 'F':
        if(curr->next!=NULL) {
          if(!rev.is_empty() && curr->next==rev.top()) curr=rev.pop();
          else curr=curr->next;
        }
        break;
      case 'B':
        if(curr->prev!=NULL) curr=curr->prev;
        break;
      case 'C':
        scan_integer(at);
        #ifdef debug
        cout << "Try to combine " <<at<<endl;
        #endif
        if(curr->next!=NULL) {
          if(!rev.is_empty() && curr->next==rev.top()) {
            #ifdef debug
            cout << "Reverse in progress during new combine!\n";
            printf("Try to remove (%d,%d)\n",rev.top()->data,rev.bottom()->data);
            #endif
            tmpp = rev.top();

            tmpp->next = NULL;
            tmpp->head = rev.bottom()->data;
            tmpp->tail = tmpp->data;

            rev.bottom()->head = rev.bottom()->data;
            rev.bottom()->tail = tmpp->data;
            rev.bottom()->prev = NULL;

            rev.remove();
            
          } else {
            curr = curr->next;
            tmpp = curr;
            curr = curr->prev;

            tmpp->prev = NULL;
            tmpp->head = tmpp->data;
            //tmpp->tail = lastTail;

            node[lastTail]->head = tmpp->data;
            //node[lastTail]->tail = lastTail;
          }
        
          /*
            curr - Last node before the unchained
            tmpp - Unchained head node
            <[curr]> ---X-CUT-X--- <[tmpp]> <[...]> <[...]
              ^                       ^
            new lastTail          new head of old lastTail
          */
          

          //lastTail = curr->data;
          //node[lastHead]->tail = lastTail;
          //curr->tail = lastTail;
        

          //updateLast(curr, lastHead, lastTail);
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
          if(!rev.is_empty()) {
            tmpp = rev.top();

            /*
            7
            6
            5
            4
            */

            tmpp->next = NULL;

            tmpp->head = rev.bottom()->data;
            tmpp->tail = tmpp->data;
            rev.bottom()->head = rev.bottom()->data;
            rev.bottom()->tail = tmpp->data;

            rev.remove();
          }
          rev.push_list(node[at]);
          node[at] = rev.pop();
        }
        
        /*if(curr->next!=NULL) {
          curr->next->prev = NULL;
        }*/        

        //node[at]->head = lastHead;
        tmp = 0;
        if(node[at]->tail!=0) tmp = node[at]->tail;
        else if(node[at]->head!=0) tmp = node[node[at]->head]->tail;
        if(tmp!=0) {
          node[tmp]->head = lastHead;
          //node[lastHead]->tail = node[at]->tail;
        }
        node[at]->prev = curr;    

        curr->next = node[at]; 
        curr = curr->next;
        
        updateLast(curr, lastHead, lastTail);
        
        break;
    }
  
    //cout << ""<< curr->data << endl;
    #ifdef debug
    //print_list(node[1]);
    if(curr==NULL) cout<<"curr is NULL!!!" <<endl;
    printf("\t");
    #endif
    curr->head = lastHead;
    lastTail = curr->data;
    node[lastHead]->tail = lastTail;
    printf("%d\n",curr->data);
  }
  return 0;
}