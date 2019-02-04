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
  public:
    int size = 0;
    void insert_front(int data);
    void delete_at(int k);
    void print_list();
};
void List::insert_front(int data) {
  Node* newNode = new Node(data, header);
  header = newNode;
  size++;
}
void List::delete_at(int k) {
  if(k > size) return;
  //cout << "delete_at" << k << ","<<size<<endl;
  Node* p = header;
  Node* tmp;
  for(int i=1;i<k-1;i++) {
    //cout << "next" << endl;
    p = p->next;
  }
  if (size == 1) {
    tmp = p;
    header = NULL;
  } else if (k==1) {
    tmp = p;
    header = p->next;
  } else {
    tmp = p->next;
    p->next = tmp->next;
  }
  size--;
  delete tmp;
}
void List::print_list() {
  //if (size==0) return;

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
  char cmd; int inp;
  for (int i=0;i<m;i++) {
    cin >> cmd >> inp;
    switch(cmd) {
      case 'I':list.insert_front(inp);break;
      case 'D':list.delete_at(inp);break;
    }
    //cout << "-------" << endl;
    //list.print_list();
    //cout << "-------" << endl;
  }
  list.print_list();

  return 0;
}