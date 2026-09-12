#include <iostream>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
};

// Cola validada en cola.cpp (misma lógica, sin el campo prev que no usa).
template <typename T> class Queue {
private:
  Node<T> *front_;
  Node<T> *back_;
  int size;

public:
  Queue() {
    front_ = nullptr;
    back_ = nullptr;
    size = 0;
  }

  ~Queue() {
    Node<T> *temp = front_;
    while (temp != nullptr) {
      Node<T> *next = temp->next;
      delete temp;
      temp = next;
    }
    front_ = nullptr;
    back_ = nullptr;
    size = 0;
  }

  void enqueue(T x) {
    Node<T> *x_ = new Node<T>{x, nullptr};
    if (size == 0) {
      front_ = x_;
    } else {
      back_->next = x_;
    }
    back_ = x_;
    size++;
  }

  void dequeue() {
    if (size == 0) {
      return;
    }
    Node<T> *temp = front_;
    front_ = front_->next;
    if (front_ == nullptr) {
      back_ = nullptr;
    }
    delete temp;
    size--;
  }

  T front() { return front_->data; }

  bool empty() { return size == 0; }

  // Swap por punteros (O(1)): evita copiar objetos Queue por valor, que
  // haría doble free al tener dos destructores borrando los mismos nodos.
  void swapWith(Queue<T> &other) {
    Node<T> *tf = front_, *tb = back_;
    int ts = size;
    front_ = other.front_;
    back_ = other.back_;
    size = other.size;
    other.front_ = tf;
    other.back_ = tb;
    other.size = ts;
  }
};

// Pila implementada con dos colas.
// Idea: q1_ guarda los elementos en orden de pila (el tope siempre
// queda al FRENTE de q1_). Al hacer push(x): se encola x en q2_, se
// pasan todos los elementos viejos de q1_ detrás de x (en q2_), y se
// intercambian los nombres de q1_/q2_. Así el elemento nuevo siempre
// termina al frente. Con esto, push queda O(n) y pop/top quedan O(1).
// (La alternativa simétrica sería push O(1) y pop O(n); acá se optó
// por hacer pesado el push porque el contrato de Pila pide pop/top
// O(1) sin excepción, y "amortizado" no aplica igual que con colas
// desde pilas: no hay forma de que las 4 operaciones queden O(1) real
// con dos colas, siempre una de las dos paga el costo de reordenar).
template <typename T> class StackFromQueues {
private:
  Queue<T> q1_;
  Queue<T> q2_;

public:
  void push(T x) {
    // O(n)
    q2_.enqueue(x);
    while (!q1_.empty()) {
      q2_.enqueue(q1_.front());
      q1_.dequeue();
    }
    // swap manual: q1_ pasa a ser la que tiene todo en orden de pila.
    q1_.swapWith(q2_);
  }

  void pop() {
    // O(1)
    q1_.dequeue();
  }

  T top() {
    // O(1)
    return q1_.front();
  }

  bool empty() { return q1_.empty(); }
};

int main() {
  StackFromQueues<int> s;

  cout << "empty al inicio: " << s.empty() << endl; // 1

  s.push(1);
  s.push(2);
  s.push(3);
  cout << "top deberia ser 3: " << s.top() << endl;

  s.pop(); // saca 3
  cout << "top tras pop, deberia ser 2: " << s.top() << endl;

  s.push(9);
  cout << "top tras push(9), deberia ser 9: " << s.top() << endl;

  cout << "orden de salida (LIFO esperado: 9 2 1): ";
  while (!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;

  cout << "empty al final: " << s.empty() << endl; // 1

  return 0;
}
