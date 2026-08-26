
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

};

int main() { return 0; }
