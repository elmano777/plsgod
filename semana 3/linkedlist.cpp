#include <iostream>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
};

template <typename T> class LinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int size;

public:
  LinkedList<T>() {
    head = nullptr;
    tail = nullptr;
    size = 0;
  };
  LinkedList(T val) {
    head = new Node<T>{val, nullptr};
    tail = head;
    size = 1;
  }
  void push_front(T val) {
    if (this->size == 0) {
      head = new Node<T>{val, nullptr};
      tail = head;
      size = 1;
      return;
    }
    Node<T> *temp = new Node<T>{val, nullptr};
    temp->next = head;
    head = temp;
    size++;
  }
  void push_back(T val) {
    if (this->size == 0) {
      head = new Node<T>{val, nullptr};
      tail = head;
      size = 1;
      return;
    }
    Node<T> *temp = new Node<T>{val, nullptr};
    tail->next = temp;
    tail = temp;
    size++;
  }
  void pop_front() {
    if (this->size == 0) {
      return;
    }
    Node<T> *temp = head;
    head = temp->next;
    delete temp;
    size--;
    if (size == 0) {
      tail = nullptr;
    }
  }
  Node<T> *front() { return head; }
  Node<T> *back() { return tail; }
  bool find(T val) {
    Node<T> *temp = head;
    while (temp) {
      if (temp->data == val) {
        return true;
      }
      temp = temp->next;
    }
    return false;
  }
  void print() {
    Node<T> *temp = head;
    while (temp) {
      cout << temp->data << " ";
      temp = temp->next;
    }
    cout << endl;
  }
  int Size() { return this->size; }
  bool empty() { return size == 0; }
  void insert(int pos, T val) {
    if (pos < 0 || pos > size) {
      return;
    }
    if (pos == 0) {
      push_front(val);
      return;
    }
    Node<T> *prev = head;
    for (int i = 0; i < pos - 1; i++) {
      prev = prev->next;
    }
    Node<T> *temp = new Node<T>{val, prev->next};
    prev->next = temp;
    if (prev == tail) {
      tail = temp;
    }
    size++;
  }
  void remove(int pos) {
    if (pos <= 0 || pos > size) {
      return;
    }
    if (pos == 1) {
      pop_front();
      return;
    }
    Node<T> *prev = head;
    for (int i = 0; i < pos - 2; i++) {
      prev = prev->next;
    }
    Node<T> *temp = prev->next;
    prev->next = temp->next;
    if (temp == tail) {
      tail = prev;
    }
    delete temp;
    size--;
  }
  void removeVal(T data) {
    if (size == 0) {
      return;
    }
    if (head->data == data) {
      pop_front();
      return;
    }
    Node<T> *prev = head;
    while (prev->next && prev->next->data != data) {
      prev = prev->next;
    }
    if (!prev->next) {
      return;
    }
    Node<T> *temp = prev->next;
    prev->next = temp->next;
    if (temp == tail) {
      tail = prev;
    }
    delete temp;
    size--;
  }
  ~LinkedList() {
    Node<T> *temp = head;
    while (temp) {
      Node<T> *next = temp->next;
      delete temp;
      temp = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
  }
};

int main() {
  LinkedList<int> l;

  cout << "=== push_back ===" << endl;
  l.push_back(10);
  l.push_back(20);
  l.push_back(30);
  l.print(); // 10 20 30

  cout << "=== push_front ===" << endl;
  l.push_front(5);
  l.print(); // 5 10 20 30

  cout << "=== size / empty ===" << endl;
  cout << l.Size() << endl; // 4
  cout << l.empty() << endl; // 0

  cout << "=== front / back ===" << endl;
  cout << l.front()->data << endl; // 5
  cout << l.back()->data << endl;  // 30

  cout << "=== find ===" << endl;
  cout << l.find(20) << endl; // 1
  cout << l.find(99) << endl; // 0

  cout << "=== insert ===" << endl;
  l.insert(2, 15); // en pos 2: 5 10 15 20 30
  l.print();

  cout << "=== remove (pos) ===" << endl;
  l.remove(3); // borra el 20 -> 5 10 15 30
  l.print();

  cout << "=== removeVal ===" << endl;
  l.removeVal(15); // borra el 15 -> 5 10 30
  l.print();

  cout << "=== pop_front hasta vaciar ===" << endl;
  l.pop_front();
  l.pop_front();
  l.pop_front();
  l.print(); // nada
  cout << l.empty() << endl; // 1

  return 0;
}
