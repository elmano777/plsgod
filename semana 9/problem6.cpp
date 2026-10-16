#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
using namespace std;

class AVL {
  struct Nodo {
    int clave;
    Nodo *izq;
    Nodo *der;
    int altura;
  };

  Nodo *raiz = nullptr;
  int contadorRotaciones = 0;

  static int h(Nodo *v) { return v ? v->altura : -1; }
  static void actualizar(Nodo *v) { v->altura = 1 + max(h(v->izq), h(v->der)); }
  static int fb(Nodo *v) { return h(v->izq) - h(v->der); }

  Nodo *rotarDerecha(Nodo *y) {
    Nodo *x = y->izq;
    y->izq = x->der;
    x->der = y;
    actualizar(y);
    actualizar(x);
    contadorRotaciones++;
    return x;
  }
  Nodo *rotarIzquierda(Nodo *x) {
    Nodo *y = x->der;
    x->der = y->izq;
    y->izq = x;
    actualizar(x);
    actualizar(y);
    contadorRotaciones++;
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

  Nodo *insertar(Nodo *v, int k) {
    if (v == nullptr) {
      return new Nodo{k, nullptr, nullptr, 0};
    }
    if (k < v->clave) {
      v->izq = insertar(v->izq, k);
    } else {
      v->der = insertar(v->der, k);
    }
    return rebalancear(v);
  }

  static Nodo *minimo(Nodo *v) {
    if (v == nullptr) {
      return nullptr;
    }
    while (v->izq) {
      v = v->izq;
    }
    return v;
  }

  static Nodo *maximo(Nodo *v) {
    if (v == nullptr) {
      return nullptr;
    }
    while (v->der) {
      v = v->der;
    }
    return v;
  }

  Nodo *eliminar(Nodo *v, int k) {
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

  static Nodo *buscar(Nodo *v, int k) {
    if (v == nullptr) {
      return nullptr;
    }
    if (v->clave == k) {
      return v;
    }
    if (k < v->clave) {
      return buscar(v->izq, k);
    }
    return buscar(v->der, k);
  }

  static int verificar(Nodo *v, long long lo, long long hi) {
    if (v == nullptr) {
      return -1;
    }
    if (v->clave <= lo || v->clave >= hi) {
      return INT_MIN;
    }
    int alturaIzq = verificar(v->izq, lo, v->clave);
    if (alturaIzq == INT_MIN) {
      return INT_MIN;
    }
    int alturaDer = verificar(v->der, v->clave, hi);
    if (alturaDer == INT_MIN) {
      return INT_MIN;
    }
    if (v->altura != 1 + max(alturaIzq, alturaDer)) {
      return INT_MIN;
    }
    if (abs(alturaIzq - alturaDer) > 1) {
      return INT_MIN;
    }
    return v->altura;
  }

  static string mostrar(Nodo *v) {
    if (v == nullptr) {
      return "";
    }
    string s = to_string(v->clave);
    if (v->izq || v->der) {
      s += "[" + mostrar(v->izq) + "," + mostrar(v->der) + "]";
    }
    return s;
  }

  static void liberar(Nodo *v) {
    if (v == nullptr) {
      return;
    }
    liberar(v->izq);
    liberar(v->der);
    delete v;
  }

  int masCercano(Nodo *v, int x) const {
    long long mayor = LLONG_MAX;
    long long menor = LLONG_MIN;
    while (v != nullptr) {
      if (v->clave == x) {
        return x;
      }
      if (v->clave < x) {
        menor = v->clave;
        v = v->der;
      } else {
        mayor = v->clave;
        v = v->izq;
      }
    }
    if (menor == LLONG_MIN) {
      return mayor;
    } else if (mayor == LLONG_MAX) {
      return menor;
    }
    long long rpta1 = mayor - x;
    long long rpta2 = x - menor;
    if (rpta1 < rpta2) {
      return mayor;
    } else {
      if (menor < mayor) {
        return menor;
      } else {
        return mayor;
      }
    }
    return menor;
  }

public:
  AVL() = default;
  ~AVL() { liberar(raiz); }
  AVL(const AVL &) = delete;
  AVL &operator=(const AVL &) = delete;

  void insertar(int k) { raiz = insertar(raiz, k); }
  void eliminar(int k) { raiz = eliminar(raiz, k); }
  bool contiene(int k) const { return buscar(raiz, k) != nullptr; }

  bool vacio() const { return raiz == nullptr; }
  int minimo() const { return minimo(raiz)->clave; }
  int maximo() const { return maximo(raiz)->clave; }

  int altura() const { return h(raiz); }
  int rotaciones() const { return contadorRotaciones; }
  void reiniciarRotaciones() { contadorRotaciones = 0; }

  bool esAVL() const {
    return verificar(raiz, LLONG_MIN, LLONG_MAX) != INT_MIN;
  }
  string mostrar() const { return mostrar(raiz); }
  int raizG() const { return raiz ? raiz->clave : 0; }
  int masCercano_(int p) const { return masCercano(raiz, p); }
};

int fallos = 0;

void check(const string &nombre, bool ok) {
  cout << (ok ? "[OK]   " : "[FAIL] ") << nombre << "\n";
  if (!ok) {
    fallos++;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  AVL av;
  int x;
  cin >> x;
  while (x--) {
    int in;
    cin >> in;
    if (in == 1) {
      int ag;
      cin >> ag;
      av.insertar(ag);
    } else if (in == 2) {
      int de;
      cin >> de;
      av.eliminar(de);
    } else {
      int ap;
      cin >> ap;
      cout << av.masCercano_(ap) << "\n";
    }
  }
  return 0;
}
