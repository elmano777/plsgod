#include <iostream>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
};

template <typename T> class CircularLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int size;

public:
  CircularLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  void push_front(T val) {
    Node<T> *temp = new Node<T>{val, nullptr};
    if (size == 0) {
      head = temp;
      tail = temp;
    } else {
      temp->next = head;
      head = temp;
    }
    tail->next = head;
    size++;
  }

  void push_back(T val) {
    Node<T> *temp = new Node<T>{val, nullptr};
    if (size == 0) {
      head = temp;
      tail = temp;
    } else {
      temp->next = head;
      tail->next = temp;
      tail = temp;
    }
    tail->next = head;
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
      Node<T> *prev = head;
      while (prev->next != tail) {
        prev = prev->next;
      }
      delete tail;
      tail = prev;
      tail->next = head;
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
    Node<T> *temp = new Node<T>{val, prev->next};
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
    if (temp == tail) {
      tail = prev;
      tail->next = head;
    }
    delete temp;
    size--;
  }

  T at(int pos) {
    if (pos <= 0 || pos > size) {
      return T();
    }
    Node<T> *temp = head;
    for (int i = 1; i < pos; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  ~CircularLinkedList() {
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
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  CircularLinkedList<int> list;
  int can;
  cin >> can;
  if (can == 1 || can == 0) {
    cout << can << endl;
    return 0;
  }
  int val = 1;
  for (int i = 0; i < can; i++) {
    list.push_back(val);
    val++;
  }
  int start = 2;
  if (list.Size() % 2 == 0) {
    while (can--) {
      cout << list.at(start) << endl;
      start += 2;
      if (start > list.Size()) {
        start = ((start - 1) % list.Size());
      }
    }
  } else {
    while (can--) {
      cout << list.at(start) << endl;
      start += 2;
      if (start > list.Size()) {
        start = ((start) % list.Size());
      }
    }
  }
  return 0;
}
