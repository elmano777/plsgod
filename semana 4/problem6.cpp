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

const long long LIMIT = 4294967296LL;

long long rpta(Stack<long long> &tn, int can, bool &overflow) {
  long long x = 0;
  overflow = false;
  while (can--) {
    string to;
    cin >> to;
    if (to == "for") {
      int n;
      cin >> n;
      long long mult = tn.top() * n;
      if (mult > LIMIT) {
        mult = LIMIT;
      }
      tn.push(mult);
    } else if (to == "end") {
      tn.pop();
    } else {
      if (!overflow) {
        x += tn.top();
        if (x > LIMIT - 1) {
          overflow = true;
        }
      }
    }
  }
  return x;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int can;
  cin >> can;
  Stack<long long> tn;
  tn.push(1);
  bool overflow;
  long long resultado = rpta(tn, can, overflow);
  if (overflow) {
    cout << "OVERFLOW!!!" << endl;
  } else {
    cout << resultado << endl;
  }
  return 0;
}
