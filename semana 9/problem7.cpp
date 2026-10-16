#include <algorithm>
#include <iostream>
using namespace std;

class AVL {
  struct Nodo {
    int clave;
    int fin;
    Nodo *izq;
    Nodo *der;
    int altura;
  };

  Nodo *raiz = nullptr;

  static int h(Nodo *v) { return v ? v->altura : -1; }
  static void actualizar(Nodo *v) { v->altura = 1 + max(h(v->izq), h(v->der)); }
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

  Nodo *insertar(Nodo *v, int s, int e) {
    if (v == nullptr) {
      return new Nodo{s, e, nullptr, nullptr, 0};
    }
    if (s < v->clave) {
      v->izq = insertar(v->izq, s, e);
    } else {
      v->der = insertar(v->der, s, e);
    }
    return rebalancear(v);
  }

  static Nodo *minimo(Nodo *v) {
    while (v->izq) {
      v = v->izq;
    }
    return v;
  }

  Nodo *eliminar(Nodo *v, int s) {
    if (v == nullptr) {
      return nullptr;
    }
    if (s < v->clave) {
      v->izq = eliminar(v->izq, s);
    } else if (s > v->clave) {
      v->der = eliminar(v->der, s);
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
      Nodo *m = minimo(v->der);
      v->clave = m->clave;
      v->fin = m->fin;
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

  void insertar(int s, int e) { raiz = insertar(raiz, s, e); }
  void eliminar(int s) { raiz = eliminar(raiz, s); }

  bool hayChoque(int s, int e) const {
    Nodo *v = raiz;
    Nodo *piso = nullptr;
    Nodo *sucesor = nullptr;
    while (v != nullptr) {
      if (v->clave <= s) {
        piso = v;
        v = v->der;
      } else {
        sucesor = v;
        v = v->izq;
      }
    }
    if (piso != nullptr && piso->fin > s) {
      return true;
    }
    if (sucesor != nullptr && sucesor->clave < e) {
      return true;
    }
    return false;
  }

  bool ocupante(int t, int &s, int &e) const {
    Nodo *v = raiz;
    Nodo *piso = nullptr;
    while (v != nullptr) {
      if (v->clave <= t) {
        piso = v;
        v = v->der;
      } else {
        v = v->izq;
      }
    }
    if (piso != nullptr && piso->fin > t) {
      s = piso->clave;
      e = piso->fin;
      return true;
    }
    return false;
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
      int s, e;
      cin >> s >> e;
      if (av.hayChoque(s, e)) {
        cout << "NO\n";
      } else {
        av.insertar(s, e);
        cout << "SI\n";
      }
    } else if (op == 2) {
      int s;
      cin >> s;
      av.eliminar(s);
    } else {
      int t, s, e;
      cin >> t;
      if (av.ocupante(t, s, e)) {
        cout << s << " " << e << "\n";
      } else {
        cout << "LIBRE\n";
      }
    }
  }
  return 0;
}
