#include <algorithm>
#include <iostream>
using namespace std;

class AVL {
  struct Nodo {
    long long clave;
    Nodo *izq;
    Nodo *der;
    int altura;
    long long suma;
  };

  Nodo *raiz = nullptr;

  static int h(Nodo *v) { return v ? v->altura : -1; }
  static long long sumaDe(Nodo *v) { return v ? v->suma : 0; }
  static void actualizar(Nodo *v) {
    v->altura = 1 + max(h(v->izq), h(v->der));
    v->suma = v->clave + sumaDe(v->izq) + sumaDe(v->der);
  }
  static int fb(Nodo *v) { return h(v->izq) - h(v->der); }

  Nodo *rotarDerecha(Nodo *y) {
    Nodo *x = y->izq;
    y->izq = x->der;
    x->der = y;
    actualizar(y);
    actualizar(x);
    return x;
  }
  Nodo *rotarIzquierda(Nodo *x) {
    Nodo *y = x->der;
    x->der = y->izq;
    y->izq = x;
    actualizar(x);
    actualizar(y);
    return y;
  }

  Nodo *rebalancear(Nodo *v) {
    actualizar(v);
    if (fb(v) > 1) {
      if (fb(v->izq) < 0) {
        v->izq = rotarIzquierda(v->izq);
      }
      return rotarDerecha(v);
    }
    if (fb(v) < -1) {
      if (fb(v->der) > 0) {
        v->der = rotarDerecha(v->der);
      }
      return rotarIzquierda(v);
    }
    return v;
  }

  Nodo *insertar(Nodo *v, long long k) {
    if (v == nullptr) {
      return new Nodo{k, nullptr, nullptr, 0, k};
    }
    if (k < v->clave) {
      v->izq = insertar(v->izq, k);
    } else {
      v->der = insertar(v->der, k);
    }
    return rebalancear(v);
  }

  static Nodo *minimo(Nodo *v) {
    while (v->izq) {
      v = v->izq;
    }
    return v;
  }

  Nodo *eliminar(Nodo *v, long long k) {
    if (v == nullptr) {
      return nullptr;
    }
    if (k < v->clave) {
      v->izq = eliminar(v->izq, k);
    } else if (k > v->clave) {
      v->der = eliminar(v->der, k);
    } else {
      if (!v->izq) {
        Nodo *temp = v->der;
        delete v;
        return temp;
      }
      if (!v->der) {
        Nodo *temp = v->izq;
        delete v;
        return temp;
      }
      v->clave = minimo(v->der)->clave;
      v->der = eliminar(v->der, v->clave);
    }
    return rebalancear(v);
  }

  static void liberar(Nodo *v) {
    if (v == nullptr) {
      return;
    }
    liberar(v->izq);
    liberar(v->der);
    delete v;
  }

public:
  AVL() = default;
  ~AVL() { liberar(raiz); }
  AVL(const AVL &) = delete;
  AVL &operator=(const AVL &) = delete;

  void insertar(long long k) { raiz = insertar(raiz, k); }
  void eliminar(long long k) { raiz = eliminar(raiz, k); }

  long long sumaMenores(long long x) const {
    Nodo *v = raiz;
    long long s = 0;
    while (v != nullptr) {
      if (v->clave < x) {
        s += v->clave + sumaDe(v->izq);
        v = v->der;
      } else {
        v = v->izq;
      }
    }
    return s;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  AVL av;
  int q;
  cin >> q;
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      long long x;
      cin >> x;
      av.insertar(x);
    } else if (op == 2) {
      long long x;
      cin >> x;
      av.eliminar(x);
    } else {
      long long l, r;
      cin >> l >> r;
      cout << av.sumaMenores(r + 1) - av.sumaMenores(l) << "\n";
    }
  }
  return 0;
}
