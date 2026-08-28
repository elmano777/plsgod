#include <iostream>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
  Node *prev;
};

template <typename T> class DoubleLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int size;

public:
  DoubleLinkedList<T>() {
    head = nullptr;
    tail = nullptr;
    size = 0;
  };
  DoubleLinkedList(T val) {
    head = new Node<T>{val, nullptr};
    tail = head;
    size = 1;
  }
  void push_front(T val) {
    if (this->size == 0) {
      head = new Node<T>{val, nullptr, nullptr};
      tail = head;
      size = 1;
      return;
    }
    Node<T> *temp = new Node<T>{val, head, nullptr};
    head->prev = temp;
    head = temp;
    size++;
  }
  void push_back(T val) {
    if (this->size == 0) {
      head = new Node<T>{val, nullptr, nullptr};
      tail = head;
      size = 1;
      return;
    }
    Node<T> *temp = new Node<T>{val, nullptr, tail};
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
    Node<T> *temp = new Node<T>{val, prev->next, prev};
    if (prev->next) {
      prev->next->prev = temp;
    }
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
    if (temp->next) {
      temp->next->prev = prev;
    }
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
    if (temp->next) {
      temp->next->prev = prev;
    }
    if (temp == tail) {
      tail = prev;
    }
    delete temp;
    size--;
  }
  ~DoubleLinkedList() {
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

int main() { return 0; }
