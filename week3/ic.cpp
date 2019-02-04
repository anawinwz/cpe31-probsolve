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
    Node* header = NULL;
    Node* tail = NULL;
  public:
    int size = 0;
    void insert_front(int data);
    void append_last(int data);
    void head_to_tail();
    void tail_to_head();
    void print_list();
};
void List::insert_front(int data) {
  Node* newNode = new Node(data, header);
  header = newNode;
  size++;
  if (size==1) tail = header;
}
void List::append_last(int data) {
  Node* newNode = new Node(data, NULL);
  if (tail) tail->next = newNode;
  tail = newNode;
  size++;
  if (size==1) header = tail;
}
void List::head_to_tail() {
  if (size==1) return;
  Node* tmp = header;
  header = header->next;
  tmp->next = NULL;
  tail->next = tmp;
  tail = tmp;
}
void List::tail_to_head() {
  if (size==1) return;
  Node* tmp;
  Node* p = header;
  while (p->next!=NULL && p->next->next!=NULL) {
    p = p->next;
  }
  tmp = p->next;
  p->next = NULL;
  tail = p;
  tmp->next = header;
  header = tmp;
}
void List::print_list() {
  Node* p = header;
  while (p!=NULL) {
    cout << p->data << endl;
    p = p->next;
  }
}
int main() {
  List list;
  int m;
  cin >> m;
  char cmd[3]; int inp;
  for (int i=0;i<m;i++) {
    cin >> cmd;
    if (cmd[1]=='i') {
      cin >> inp;
      switch(cmd[0]){
        case 'l':list.insert_front(inp);break;
        case 'r':list.append_last(inp);break;
      }
    } else {
      switch(cmd[0]) {
        case 'l':list.head_to_tail();break;
        case 'r':list.tail_to_head();break;
      }
      /*cout << "-------" << endl;
      list.print_list();
      cout << "-------" << endl;*/
    }
    /*cout << "-------" << endl;
    list.print_list();
    cout << "-------" << endl;*/
  }
  list.print_list();

  return 0;
}