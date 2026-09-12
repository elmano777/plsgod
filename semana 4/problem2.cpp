#include <iostream>
#include <utility>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
  Node *prev;
};

template <typename T> class Queue {
private:
  int size;
  Node<T> *front_;
  Node<T> *back_;

public:
  Queue() {
    size = 0;
    front_ = nullptr;
    back_ = nullptr;
  }
  ~Queue() {
    if (size == 0) {
      return;
    }
    while (front_ != nullptr) {
      Node<T> *temp = front_;
      front_ = front_->next;
      delete temp;
    }
    size = 0;
    front_ = nullptr;
    back_ = nullptr;
  }

  void enqueue(T x) {
    if (size == 0) {
      size++;
      Node<T> *an = new Node<T>{x, nullptr, nullptr};
      front_ = an;
      back_ = an;
      return;
    }
    Node<T> *an = new Node<T>{x, nullptr, back_};
    back_->next = an;
    back_ = an;
    size++;
  }

  void dequeue() {
    if (size == 0) {
      return;
    }
    Node<T> *temp = front_;
    front_ = front_->next;
    delete temp;
    size--;
    if (front_ == nullptr) {
      back_ = nullptr;
    }
  }

  T front() { return front_->data; }

  bool empty() { return size == 0; }

  T back() { return back_->data; }
};

int main() {
  int n, m;
  cin >> n >> m;
  Queue<pair<int, int>> col;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    col.enqueue({i, a});
  }
  int last_home = -1;
  while (!col.empty()) {
    pair<int, int> child = col.front();
    col.dequeue();
    int idx = child.first;
    int falta = child.second - m;
    if (falta <= 0) {
      last_home = idx;
    } else {
      col.enqueue({idx, falta});
    }
  }
  cout << last_home << endl;
  return 0;
}
