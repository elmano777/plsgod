#include <iostream>
#include <string>

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
  int can;
  cin >> can;
  Stack<int> tn;
  while (can--) {
    string to;
    cin >> to;
    if (to == "+" || to == "-" || to == "*" || to == "/") {
      int b = tn.top();
      tn.pop();
      int a = tn.top();
      tn.pop();
      int res;
      if (to == "+")
        res = a + b;
      else if (to == "-")
        res = a - b;
      else if (to == "*")
        res = a * b;
      else
        res = a / b;
      tn.push(res);
    } else {
      int val = stoi(to);
      tn.push(val);
    }
  }
  cout << tn.top() << endl;
  return 0;
}
