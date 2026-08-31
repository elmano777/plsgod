#include <iostream>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
  Node *prev;
};

template <typename T> class CircularDoubleLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int size;

public:
  CircularDoubleLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  void push_front(T val) {
    Node<T> *temp = new Node<T>{val, nullptr, nullptr};
    if (size == 0) {
      head = temp;
      tail = temp;
    } else {
      temp->next = head;
      head->prev = temp;
      head = temp;
    }
    tail->next = head;
    head->prev = tail;
    size++;
  }

  void push_back(T val) {
    Node<T> *temp = new Node<T>{val, nullptr, nullptr};
    if (size == 0) {
      head = temp;
      tail = temp;
    } else {
      temp->prev = tail;
      tail->next = temp;
      tail = temp;
    }
    tail->next = head;
    head->prev = tail;
    size++;
  }

  void pop_front() {
    if (size == 0) {
      return;
    }
    if (size == 1) {
      delete head;
      head = nullptr;
      tail = nullptr;
    } else {
      Node<T> *temp = head;
      head = head->next;
      tail->next = head;
      head->prev = tail;
      delete temp;
    }
    size--;
  }

  void pop_back() {
    if (size == 0) {
      return;
    }
    if (size == 1) {
      delete head;
      head = nullptr;
      tail = nullptr;
    } else {
      Node<T> *temp = tail;
      tail = tail->prev;
      tail->next = head;
      head->prev = tail;
      delete temp;
    }
    size--;
  }

  Node<T> *front() { return head; }
  Node<T> *back() { return tail; }

  bool find(T val) {
    if (size == 0) {
      return false;
    }
    Node<T> *temp = head;
    while (true) {
      if (temp->data == val) {
        return true;
      }
      temp = temp->next;
      if (temp == head) {
        break;
      }
    }
    return false;
  }

  void print() {
    if (size == 0) {
      return;
    }
    Node<T> *temp = head;
    while (true) {
      cout << temp->data << " ";
      temp = temp->next;
      if (temp == head) {
        break;
      }
    }
    cout << endl;
  }

  int Size() { return size; }
  bool empty() { return size == 0; }

  void insert(int pos, T val) {
    if (pos < 0 || pos > size) {
      return;
    }
    if (pos == 0) {
      push_front(val);
      return;
    }
    if (pos == size) {
      push_back(val);
      return;
    }
    Node<T> *prev = head;
    for (int i = 0; i < pos - 1; i++) {
      prev = prev->next;
    }
    Node<T> *temp = new Node<T>{val, prev->next, prev};
    prev->next->prev = temp;
    prev->next = temp;
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
    temp->next->prev = prev;
    if (temp == tail) {
      tail = prev;
      tail->next = head;
      head->prev = tail;
    }
    delete temp;
    size--;
  }

  ~CircularDoubleLinkedList() {
    if (size == 0) {
      return;
    }
    Node<T> *temp = head;
    while (temp != tail) {
      Node<T> *next = temp->next;
      delete temp;
      temp = next;
    }
    delete tail;
    head = nullptr;
    tail = nullptr;
    size = 0;
  }
};

int main() {
  CircularDoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_front(0);
  list.print();

  list.insert(1, 9);
  list.print();

  list.remove(4);
  list.print();

  list.pop_front();
  list.pop_back();
  list.print();

  cout << (list.find(2) ? "si existe" : "no existe") << endl;
  return 0;
}