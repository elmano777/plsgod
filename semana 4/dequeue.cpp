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
};

int main() {
  Dequeue<int> d;

  cout << "empty al inicio: " << d.empty() << endl; // 1 (true)

  d.push_back(2);
  d.push_back(3);
  d.push_front(1);
  // deque actual: 1 2 3
  cout << "empty tras push_back(2), push_back(3), push_front(1): "
       << d.empty() << endl; // 0 (false)
  cout << "front deberia ser 1: " << d.front() << endl;
  cout << "back deberia ser 3: " << d.back() << endl;

  d.pop_front();
  // deque actual: 2 3
  cout << "front tras pop_front, deberia ser 2: " << d.front() << endl;

  d.pop_back();
  // deque actual: 2
  cout << "back tras pop_back, deberia ser 2: " << d.back() << endl;
  cout << "front tambien deberia ser 2 (un solo elemento): " << d.front()
       << endl;

  d.push_front(0);
  d.push_back(5);
  // deque actual: 0 2 5
  cout << "front deberia ser 0: " << d.front() << endl;
  cout << "back deberia ser 5: " << d.back() << endl;

  // Vaciar alternando pop_front/pop_back para probar ambos extremos
  cout << "vaciando (front, back, front): ";
  cout << d.front() << " ";
  d.pop_front(); // saca 0, queda: 2 5
  cout << d.back() << " ";
  d.pop_back(); // saca 5, queda: 2
  cout << d.front() << " ";
  d.pop_front(); // saca 2, queda vacia
  cout << endl;

  cout << "empty al final: " << d.empty() << endl; // 1 (true)

  // Probar que pop sobre deque vacia no crashea
  d.pop_front();
  d.pop_back();
  cout << "sigue empty tras pop en vacia (no debe crashear): " << d.empty()
       << endl;

  return 0;
}
