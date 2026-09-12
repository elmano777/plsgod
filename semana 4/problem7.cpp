#include <cstddef>
#include <iostream>
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
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int can;
  cin >> can;
  Stack<int> st;
  vector<int> rptaenv;
  Stack<int> max;
  while (can--) {
    int ver;
    cin >> ver;
    if (ver == 1) {
      int num;
      cin >> num;
      st.push(num);
      if (max.empty() || num >= max.top()) {
        max.push(num);
      } else {
        max.push(max.top());
      }
    } else if (ver == 2) {
      if (!st.empty()) {
        st.pop();
        max.pop();
      }
    } else {
      if (!max.empty()) {
        rptaenv.push_back(max.top());
      }
    }
  }
  for (size_t i = 0; i < rptaenv.size(); i++) {
    cout << rptaenv[i] << endl;
  }
  return 0;
}
