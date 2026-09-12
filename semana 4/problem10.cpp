#include <climits>
#include <iostream>
#include <vector>

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
};

int minMaxWindow(vector<int> &A, int n, int d) {
  Dequeue<int> dq;
  int minimo = INT_MAX;
  for (int i = 0; i < n; i++) {
    while (!dq.empty() && A[dq.back()] <= A[i]) {
      dq.pop_back();
    }
    dq.push_back(i);
    if (dq.front() <= i - d) {
      dq.pop_front();
    }
    if (i >= d - 1) {
      int maxVentana = A[dq.front()];
      if (maxVentana < minimo) {
        minimo = maxVentana;
      }
    }
  }
  return minimo;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  while (q--) {
    int d;
    cin >> d;
    cout << minMaxWindow(a, n, d) << "\n";
  }
  return 0;
}
