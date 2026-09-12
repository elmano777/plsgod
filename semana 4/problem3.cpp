#include <iostream>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
  Node *prev;
};

template <typename T> class Dequeue {
private:
  Node<T> *front_;
  Node<T> *back_;
  int size;

public:
  Dequeue() {
    size = 0;
    front_ = nullptr;
    back_ = nullptr;
  }
  ~Dequeue() {
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
  };
  void push_front(T x) {
    if (size == 0) {
      size++;
      Node<T> *an = new Node<T>{x, nullptr, nullptr};
      front_ = an;
      back_ = an;
      return;
    }
    Node<T> *an = new Node<T>{x, front_, nullptr};
    front_->prev = an;
    front_ = an;
    size++;
  }
  void push_back(T x) {
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
  void pop_front() {
    if (size == 0) {
      return;
    }
    Node<T> *temp = front_;
    front_ = front_->next;
    if (front_ != nullptr) {
      front_->prev = nullptr;
    } else {
      back_ = nullptr;
    }
    delete temp;
    size--;
  }
  void pop_back() {
    if (size == 0) {
      return;
    }
    Node<T> *temp = back_;
    back_ = back_->prev;
    if (back_ != nullptr) {
      back_->next = nullptr;
    } else {
      front_ = nullptr;
    }
    delete temp;
    size--;
  }
  T front() { return front_->data; }
  T back() { return back_->data; }
  bool empty() { return size == 0; }
  void reverse() {
    Node<T> *cur = front_;
    while (cur != nullptr) {
      Node<T> *next_viejo = cur->next;
      cur->next = cur->prev;
      cur->prev = next_viejo;
      cur = next_viejo;
    }
    Node<T> *temp = front_;
    front_ = back_;
    back_ = temp;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int can;
  cin >> can;
  Dequeue<int> dq;
  while (can--) {
    string cmd;
    cin >> cmd;
    if (cmd == "back") {
      if (dq.empty()) {
        cout << "No job for Ada?" << "\n";
      } else {
        cout << dq.back() << "\n";
        dq.pop_back();
      }
    } else if (cmd == "front") {
      if (dq.empty()) {
        cout << "No job for Ada?" << "\n";
      } else {
        cout << dq.front() << "\n";
        dq.pop_front();
      }
    } else if (cmd == "reverse") {
      dq.reverse();
    } else if (cmd == "push_back") {
      int x;
      cin >> x;
      dq.push_back(x);
    } else if (cmd == "toFront") {
      int x;
      cin >> x;
      dq.push_front(x);
    }
  }
  return 0;
}
