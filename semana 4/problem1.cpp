#include <iostream>
#include <string>
#include <vector>

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

  string balance(string env) {
    for (char i : env) {
      switch (i) {
      case '(':
        push(i);
        break;
      case ')':
        if (empty()) {
          return "NO";
        }
        if (top() == '(') {
          pop();
          break;
        }
        push(i);
        break;
      case '[':
        push(i);
        break;
      case ']':
        if (empty()) {
          return "NO";
        }
        if (top() == '[') {
          pop();
          break;
        }
        push(i);
        break;
      case '{':
        push(i);
        break;
      case '}':
        if (empty()) {
          return "NO";
        }
        if (top() == '{') {
          pop();
          break;
        }
        push(i);
        break;
      default:
        break;
      }
    }
    if (empty()) {
      return "YES";
    }
    return "NO";
  }
};

int main() {
  int op1;
  cin >> op1;
  vector<string> inputs(op1);
  for (int j = 0; j < op1; j++) {
    cin >> inputs[j];
  }
  for (int j = 0; j < op1; j++) {
    Stack<char> s;
    cout << s.balance(inputs[j]) << endl;
  }
  return 0;
}
