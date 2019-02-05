#include<iostream>
using namespace std;
struct Node {
  int data;
  Node* next = NULL;
  Node(int data, Node* next)
    : data(data), next(next) {}
};
class List {
  private:
    Node* tail = NULL;
  public:
    Node* header = NULL;
    int size = 0;
    void connect(List* next);
    void append_last(int data);
    void print_list();
    void reset_train();
};
void List::reset_train() {
  size = 0;
  header = NULL;
  tail = NULL;
}
void List::connect(List* next) {
  if (tail!=NULL) {
    Node* newNode = next->header;
    tail->next=newNode;
    size+=next->size;
    delete next->header;
    next->reset_train();
  }
}
void List::append_last(int data) {
  Node* newNode = new Node(data, NULL);
  if (tail) tail->next = newNode;
  tail = newNode;
  size++;
  if (size==1) header = tail;
}
void List::print_list() {
  Node* p = header;
  while (p!=NULL) {
    cout << p->data << endl;
    p = p->next;
  }
}
int main() {
  List list[100000];
  int m;
  cin >> m;
  char cmd; int x, y;
  for (int i=0;i<m;i++) {
    cin >> cmd >> x >> y;
    switch(cmd){
      case 'N':list[y-1].append_last(x);break;
      case 'M':list[y-1].connect(&list[x-1]);break;
    }
    /*cout << "-------" << endl;
    list[y-1].print_list();
    cout << "-------" << endl;*/
  }
  for(int i=0;i<100000;i++) {
    //cout << i << endl;
    list[i].print_list();
  }

  return 0;
}