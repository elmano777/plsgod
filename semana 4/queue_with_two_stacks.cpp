#include <iostream>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
};

// Pila validada en pila.cpp (misma lógica, sin el campo prev que no usa).
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

// Cola implementada con dos pilas.
// Idea: in_ recibe todo lo que entra (enqueue = push en in_, O(1)).
// out_ sirve para sacar en orden FIFO: si out_ está vacía, volcamos
// TODO in_ hacia out_ (eso invierte el orden dos veces -> vuelve a FIFO).
// Cada elemento se mueve de in_ a out_ como máximo una vez en su vida,
// así que el costo total de mover N elementos es O(N) repartido entre
// N operaciones -> O(1) amortizado por operación (no O(1) en el peor
// caso de una sola llamada, pero sí en promedio).
template <typename T> class QueueFromStacks {
private:
  Stack<T> in_;
  Stack<T> out_;

  void moveIfNeeded() {
    if (out_.empty()) {
      while (!in_.empty()) {
        out_.push(in_.top());
        in_.pop();
      }
    }
  }

public:
  void enqueue(T x) {
    // O(1) real.
    in_.push(x);
  }

  void dequeue() {
    // O(1) amortizado.
    moveIfNeeded();
    out_.pop();
  }

  T front() {
    // O(1) amortizado.
    moveIfNeeded();
    return out_.top();
  }

  bool empty() { return in_.empty() && out_.empty(); }
};

int main() {
  QueueFromStacks<int> q;

  cout << "empty al inicio: " << q.empty() << endl; // 1

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  cout << "front deberia ser 1: " << q.front() << endl;

  q.dequeue(); // saca 1
  cout << "front tras dequeue, deberia ser 2: " << q.front() << endl;

  q.enqueue(4); // entra a in_ mientras out_ todavia tiene 2,3
  cout << "front sigue siendo 2: " << q.front() << endl;

  cout << "orden de salida (FIFO esperado: 2 3 4): ";
  while (!q.empty()) {
    cout << q.front() << " ";
    q.dequeue();
  }
  cout << endl;

  cout << "empty al final: " << q.empty() << endl; // 1

  return 0;
}
