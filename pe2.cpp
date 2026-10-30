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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, K;
  cin >> n >> K;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  Dequeue<int> maxD, minD;
  long long total = 0;
  int mejor = 0;
  int l = 0;
  for (int r = 0; r < n; r++) {
    while (!maxD.empty() && a[maxD.back()] <= a[r]) {
      maxD.pop_back();
    }
    maxD.push_back(r);
    while (!minD.empty() && a[minD.back()] >= a[r]) {
      minD.pop_back();
    }
    minD.push_back(r);
    while (a[maxD.front()] - a[minD.front()] > K) {
      l++;
      if (maxD.front() < l) {
        maxD.pop_front();
      }
      if (minD.front() < l) {
        minD.pop_front();
      }
    }
    total += r - l + 1;
    if (r - l + 1 > mejor) {
      mejor = r - l + 1;
    }
  }
  cout << total << " " << mejor << "\n";
  return 0;
}
