#include <iostream>

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
  Queue<int> q;

  cout << "empty al inicio: " << q.empty() << endl; // 1 (true)

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  cout << "empty tras 3 enqueue: " << q.empty() << endl; // 0 (false)
  cout << "front deberia ser 1: " << q.front() << endl;
  cout << "back deberia ser 3: " << q.back() << endl;

  q.dequeue();
  cout << "front tras dequeue, deberia ser 2: " << q.front() << endl;

  q.enqueue(9);
  cout << "front sigue siendo 2 (enqueue no toca el frente): " << q.front()
       << endl;
  cout << "back ahora deberia ser 9: " << q.back() << endl;

  // Orden FIFO esperado al vaciar: 2 3 9
  cout << "orden de salida (FIFO): ";
  while (!q.empty()) {
    cout << q.front() << " ";
    q.dequeue();
  }
  cout << endl;

  cout << "empty al final: " << q.empty() << endl; // 1 (true)

  return 0;
}
