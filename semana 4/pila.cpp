#include <iostream>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
  Node *prev;
};

template <typename T> class Stack {
private:
  Node<T> *top_;
  int size;

public:
  Stack() {
    top_ = nullptr;
    size = 0;
  }

  ~Stack() {
    if (size == 0) {
      return;
    }
    Node<T> *temp = top_;
    while (temp != nullptr) {
      Node<T> *next = temp->next;
      delete temp;
      temp = next;
    }
    top_ = nullptr;
    size = 0;
  }

  void push(T x) {
    Node<T> *x_ = new Node<T>{x, top_, nullptr};
    top_ = x_;
    size++;
  }

  void pop() {
    if (size == 0) {
      return;
    }
    Node<T> *temp = top_;
    top_ = top_->next;
    delete temp;
    size--;
  }

  T top() { return top_->data; }

  bool empty() { return size == 0; }
};

int main() {
  Stack<int> s;

  cout << "empty al inicio: " << s.empty() << endl; // 1 (true)

  s.push(1);
  s.push(2);
  s.push(3);
  cout << "empty tras 3 push: " << s.empty() << endl; // 0 (false)
  cout << "top deberia ser 3: " << s.top() << endl;

  s.pop();
  cout << "top tras pop, deberia ser 2: " << s.top() << endl;

  s.push(9);
  cout << "top tras push(9), deberia ser 9: " << s.top() << endl;

  // Orden LIFO esperado al vaciar: 9 2 1
  cout << "orden de salida (LIFO): ";
  while (!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;

  cout << "empty al final: " << s.empty() << endl; // 1 (true)

  return 0;
}
