#include <algorithm>
#include <climits>
#include <iostream>
#include <random>
#include <set>
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
  static void actualizar(Nodo *v) {
    v->altura = 1 + max(h(v->izq), h(v->der));
  }
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

  bool esAVL() const { return verificar(raiz, LLONG_MIN, LLONG_MAX) != INT_MIN; }
  string mostrar() const { return mostrar(raiz); }
};

int fallos = 0;

void check(const string &nombre, bool ok) {
  cout << (ok ? "[OK]   " : "[FAIL] ") << nombre << "\n";
  if (!ok) {
    fallos++;
  }
}

int main() {
  {
    AVL t;
    for (int k : {10, 20, 30}) t.insertar(k);
    check("10,20,30 -> 20[10,30] con 1 rotación",
          t.mostrar() == "20[10,30]" && t.rotaciones() == 1 && t.esAVL());
  }
  {
    AVL t;
    for (int k : {30, 10, 20}) t.insertar(k);
    check("30,10,20 -> 20[10,30] con 2 rotaciones (LR)",
          t.mostrar() == "20[10,30]" && t.rotaciones() == 2 && t.esAVL());
  }
  {
    AVL t;
    for (int k : {10, 20, 30, 40, 50}) t.insertar(k);
    t.reiniciarRotaciones();
    t.insertar(25);
    check("insertar 25 -> caso RL, 2 rotaciones",
          t.rotaciones() == 2 && t.esAVL());
    cout << "       " << t.mostrar() << "\n";
  }
  {
    AVL t;
    for (int k = 1; k <= 7; k++) t.insertar(k);
    check("1..7 -> 4[2[1,3],6[5,7]], altura 2, 4 rotaciones",
          t.mostrar() == "4[2[1,3],6[5,7]]" && t.altura() == 2 &&
              t.rotaciones() == 4 && t.esAVL());
  }
  {
    AVL t;
    for (int k : {5, 3, 8, 2, 4, 7, 10, 1, 6, 9, 11, 12}) t.insertar(k);
    check("árbol de 12 claves del README",
          t.mostrar() == "5[3[2[1,],4],8[7[6,],10[9,11[,12]]]]" && t.esAVL());
    t.reiniciarRotaciones();
    t.eliminar(4);
    check("eliminar 4 -> rota en dos niveles",
          t.rotaciones() == 2 && t.esAVL() && !t.contiene(4));
    cout << "       " << t.mostrar() << "\n";
  }
  {
    AVL t;
    check("árbol vacío: vacio() y !contiene", t.vacio() && !t.contiene(1));
    t.insertar(7);
    t.eliminar(99);
    check("eliminar clave inexistente no cambia el árbol",
          t.mostrar() == "7" && t.esAVL());
  }
  {
    mt19937 rng(12345);
    AVL t;
    set<int> ref;
    bool ok = true;
    for (int i = 0; i < 20000 && ok; i++) {
      int k = rng() % 500;
      if (rng() % 2) {
        if (!ref.count(k)) {
          t.insertar(k);
          ref.insert(k);
        }
      } else {
        t.eliminar(k);
        ref.erase(k);
      }
      ok = t.esAVL() && t.contiene(k) == (ref.count(k) > 0);
      if (ok && !ref.empty()) {
        ok = t.minimo() == *ref.begin() && t.maximo() == *ref.rbegin();
      }
    }
    check("20000 operaciones aleatorias vs std::set", ok);
  }

  cout << (fallos ? "HAY FALLOS\n" : "Todo OK\n");
  return fallos != 0;
}
