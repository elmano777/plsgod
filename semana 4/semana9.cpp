#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
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
    Node<T> *x_ = new Node<T>{x, top_};
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

template <typename T> class MaxQueue {
private:
  Stack<pair<T, T>> in_, out_;

  void moveIfNeeded() {
    if (out_.empty()) {
      while (!in_.empty()) {
        T value = in_.top().first;
        in_.pop();
        T m = out_.empty() ? value : max(value, out_.top().second);
        out_.push({value, m});
      }
    }
  }

public:
  void enqueue(T x) {
    T m = in_.empty() ? x : max(x, in_.top().second);
    in_.push({x, m});
  }

  void dequeue() {
    moveIfNeeded();
    out_.pop();
  }

  T getMax() {
    moveIfNeeded();
    if (out_.empty()) {
      return in_.top().second;
    }
    if (in_.empty()) {
      return out_.top().second;
    }
    return max(out_.top().second, in_.top().second);
  }

  bool empty() { return in_.empty() && out_.empty(); }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int can;
  cin >> can;
  MaxQueue<int> q;
  vector<int> rptaenv;

  while (can--) {
    int ver;
    cin >> ver;
    if (ver == 1) {
      int num;
      cin >> num;
      q.enqueue(num);
    } else if (ver == 2) {
      if (!q.empty()) {
        q.dequeue();
      }
    } else {
      if (!q.empty()) {
        rptaenv.push_back(q.getMax());
      }
    }
  }

  for (size_t i = 0; i < rptaenv.size(); i++) {
    cout << rptaenv[i] << endl;
  }
  return 0;
}
