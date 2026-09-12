#include <array>
#include <climits>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// --- Nuestra Stack de siempre (pila.cpp), sin el campo prev que no usamos ---
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

// --- Cola armada con dos de nuestras Stacks (mismo truco de
// queue_with_two_stacks.cpp), pero cada nodo guarda ademas el
// "acumulado" de combinar (con el operador + del tipo T) todos los
// elementos desde el fondo de esa pila hasta ese nodo. Asi, el tope
// de cada pila siempre tiene, en .second, el resultado combinado de
// TODA esa pila en el orden correcto -> consultar el combinado de
// toda la cola es O(1) en vez de recorrerla entera. ---
template <typename data_type> class AssociativeQueue {
private:
  Stack<pair<data_type, data_type>> in_, out_;

public:
  void push(data_type value) {
    if (in_.empty()) {
      in_.push({value, value});
    } else {
      // in_.top().second ya es el combinado de todo lo que hay en in_;
      // como los elementos de in_ van "en orden" del mas viejo al mas
      // nuevo de abajo hacia arriba, el nuevo valor se combina a la
      // derecha del acumulado anterior.
      in_.push({value, in_.top().second + value});
    }
  }

  void pop() {
    if (out_.empty()) {
      // volcar todo in_ hacia out_, reconstruyendo el acumulado en el
      // orden correcto (el mismo truco de queue_with_two_stacks.cpp,
      // solo que ademas recalculamos el acumulado en cada paso)
      while (!in_.empty()) {
        data_type value = in_.top().first;
        in_.pop();
        if (out_.empty()) {
          out_.push({value, value});
        } else {
          out_.push({value, value + out_.top().second});
        }
      }
    }
    out_.pop();
  }

  // combinado de TODA la cola: out_ representa el frente, in_ el
  // final -> el orden correcto es out_ primero, in_ despues.
  data_type all() {
    if (out_.empty()) {
      return in_.top().second;
    }
    if (in_.empty()) {
      return out_.top().second;
    }
    return out_.top().second + in_.top().second;
  }
};

// --- Matriz modular 2x2, igual que en el archivo del profe ---
template <int MOD> struct ModularMatrix {
  array<array<int, 2>, 2> M;

  ModularMatrix() {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        M[i][j] = 0;
      }
    }
  }

  // ojo: "+" aca en realidad hace multiplicacion de matrices; es el
  // operador que la cola asociativa usa para combinar elementos.
  ModularMatrix operator+(const ModularMatrix &rhs) const {
    ModularMatrix res;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        long long cur = 0;
        for (int k = 0; k < 2; ++k) {
          cur += 1LL * M[i][k] * rhs.M[k][j];
        }
        res.M[i][j] = cur % MOD;
      }
    }
    return res;
  }

  int trace() { return (M[0][0] + M[1][1]) % MOD; }

  friend istream &operator>>(istream &is, ModularMatrix &m) {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        is >> m.M[i][j];
      }
    }
    return is;
  }
};

using Matrix = ModularMatrix<1000000007>;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vector<Matrix> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  while (q--) {
    int d;
    cin >> d;
    AssociativeQueue<Matrix> Q;
    for (int i = 0; i + 1 < d; ++i) {
      Q.push(a[i]);
    }
    int res = INT_MIN;
    for (int i = d - 1; i < n; ++i) {
      Q.push(a[i]);
      if (i >= d) {
        Q.pop();
      }
      res = max(res, Q.all().trace());
    }
    cout << res << '\n';
  }

  return 0;
}
