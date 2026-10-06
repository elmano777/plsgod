#include <iostream>

using namespace std;

template <typename T> class BST {
private:
  struct Nodo {
    T clave;
    Nodo *izq;
    Nodo *der;
    Nodo *padre;

    Nodo(const T &clave)
        : clave(clave), izq(nullptr), der(nullptr), padre(nullptr) {}
  };

  Nodo *raiz;

  void liberar(Nodo *x) {
    if (x == nullptr) {
      return;
    }
    if (x->izq) {
      liberar(x->izq);
    }
    if (x->der) {
      liberar(x->der);
    }
    delete x;
  }

  // TODO: reemplaza el subárbol de u por el de v, reconecta punteros con
  // padre(u)
  void transplantar(Nodo *u, Nodo *v) {
    if (u->padre == nullptr) {
      raiz = v;
    } else if (u->padre->izq == u) {
      u->padre->izq = v;
    } else {
      u->padre->der = v;
    }
    if (v != nullptr) {
      v->padre = u->padre;
    }
  }

  void inorder(Nodo *x) const {
    if (x == nullptr) {
      return;
    }
    inorder(x->izq);
    cout << x->clave << endl;
    inorder(x->der);
  }

  Nodo *buscar(Nodo *x, const T &k) const {
    if (x == nullptr) {
      return nullptr;
    }
    if (x->clave == k) {
      return x;
    }
    if (x->clave < k) {
      return buscar(x->der, k);
    } else {
      return buscar(x->izq, k);
    }
  }

public:
  BST() : raiz(nullptr) {}

  ~BST() { liberar(raiz); }

  // O(h)
  Nodo *buscar(const T &k) const { return buscar(raiz, k); }

  // O(h)
  Nodo *minimo(Nodo *x) const {
    if (x == nullptr) {
      return nullptr;
    }
    while (x->izq != nullptr) {
      x = x->izq;
    }
    return x;
  }

  // O(h)
  Nodo *maximo(Nodo *x) const {
    if (x == nullptr) {
      return nullptr;
    }
    while (x->der != nullptr) {
      x = x->der;
    }
    return x;
  }

  // O(h)
  void insertar(const T &k) {
    Nodo *x = raiz;
    Nodo *y = nullptr;
    while (x != nullptr) {
      y = x;
      if (x->clave < k) {
        x = x->der;
      } else {
        x = x->izq;
      }
    }
    Nodo *newN = new Nodo(k);
    newN->padre = y;
    if (y == nullptr) {
      raiz = newN;
    } else {
      if (y->clave < k) {
        y->der = newN;
      } else {
        y->izq = newN;
      }
    }
    return;
  }

  // O(h)
  Nodo *sucesor(Nodo *x) const {
    if (x == nullptr) {
      return nullptr;
    }
    if (x->der != nullptr) {
      return minimo(x->der);
    }
    Nodo *y = x->padre;
    while (y != nullptr && x == y->der) {
      x = y;
      y = y->padre;
    }
    return y;
  }

  // O(h)
  Nodo *predecesor(Nodo *x) const {
    if (x == nullptr) {
      return nullptr;
    }
    if (x->izq != nullptr) {
      return maximo(x->izq);
    }
    Nodo *y = x->padre;
    while (y != nullptr && x == y->izq) {
      x = y;
      y = y->padre;
    }
    return y;
  }

  // O(h)
  void eliminar(const T &k) {
    Nodo *z = buscar(k);
    if (z == nullptr) {
      return;
    }
    if (z->izq == nullptr) {
      transplantar(z, z->der);
    } else if (z->der == nullptr) {
      transplantar(z, z->izq);
    } else {
      Nodo *y = sucesor(z);
      if (y->padre != z) {
        transplantar(y, y->der);
        y->der = z->der;
        y->der->padre = y;
      }
      transplantar(z, y);
      y->izq = z->izq;
      y->izq->padre = y;
    }
    delete z;
  }

  // Θ(n)
  void imprimirInorder() const {
    inorder(raiz);
    std::cout << "\n";
  }
};

int main() {
  BST<int> arbol;

  // Ejemplo de la clase: insertar 8, 3, 10, 1, 6, luego 7
  // inorder esperado: 1 3 6 7 8 10
  for (int k : {8, 3, 10, 1, 6, 7}) {
    arbol.insertar(k);
  }
  arbol.imprimirInorder();

  return 0;
}
