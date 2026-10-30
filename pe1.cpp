#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename K, typename V> struct Node {
  K key;
  V value;
  Node *next;
  Node(K k, V v, Node *nex = nullptr) : key(k), value(v), next(nex) {}
};

template <typename T> long long hashRaw(T clave);

template <> long long hashRaw<int>(int clave) {
  const long long B = 311;
  const long long MOD = 1e9 + 7;
  long long hash_value = 0;
  int key = clave < 0 ? -clave : clave;
  while (key > 0) {
    int d = key % 10;
    hash_value = (hash_value * B + (d + 1)) % MOD;
    key /= 10;
  }
  return hash_value;
}

template <> long long hashRaw<string>(string clave) {
  const long long B = 131;
  const long long MOD = 1e9 + 7;
  long long hash_value = 0;
  for (char c : clave) {
    hash_value = (hash_value * B + (int)(unsigned char)c + 1) % MOD;
  }
  return hash_value;
}

template <> long long hashRaw<vector<int>>(vector<int> clave) {
  const long long B = 1000003;
  const long long MOD = 1e9 + 7;
  long long hash_value = 0;
  for (int x : clave) {
    hash_value = (hash_value * B + x + 1) % MOD;
  }
  return hash_value;
}

template <typename K, typename V> class Diccionary {
private:
  vector<Node<K, V> *> buckets;
  int n;
  int m;
  int _hash(K clave) { return (int)(hashRaw<K>(clave) % m); }

public:
  Diccionary(int m_inicial = 11) : n(0), m(m_inicial) {
    buckets.assign(m, nullptr);
  }

  ~Diccionary() {
    for (int i = 0; i < m; i++) {
      Node<K, V> *now = buckets[i];
      while (now != nullptr) {
        Node<K, V> *next = now->next;
        delete now;
        now = next;
      }
    }
  }

  bool esPrimo(int x) {
    if (x < 2) {
      return false;
    }
    for (int i = 2; 1LL * i * i <= x; i++) {
      if (x % i == 0) {
        return false;
      }
    }
    return true;
  }

  int siguientePrimo(int x) {
    while (!esPrimo(x)) {
      x++;
    }
    return x;
  }

  void rehash() {
    int m_nuevo = siguientePrimo(2 * m);
    vector<Node<K, V> *> bucketsNuevos(m_nuevo, nullptr);
    for (int i = 0; i < m; i++) {
      Node<K, V> *actual = buckets[i];
      while (actual != nullptr) {
        Node<K, V> *siguiente = actual->next;
        int idxNuevo = (int)(hashRaw<K>(actual->key) % m_nuevo);
        actual->next = bucketsNuevos[idxNuevo];
        bucketsNuevos[idxNuevo] = actual;
        actual = siguiente;
      }
    }
    buckets = bucketsNuevos;
    m = m_nuevo;
  }

  void insertar(K clave, V valor) {
    int idx = _hash(clave);
    Node<K, V> *temp = buckets[idx];
    while (temp != nullptr) {
      if (temp->key == clave) {
        temp->value = valor;
        return;
      }
      temp = temp->next;
    }
    if ((double)(n + 1) / m >= 0.75) {
      rehash();
      idx = _hash(clave);
    }
    Node<K, V> *newI = new Node<K, V>(clave, valor, buckets[idx]);
    buckets[idx] = newI;
    n++;
  }

  Node<K, V> *search(K clave) {
    int idx = _hash(clave);
    Node<K, V> *temp = buckets[idx];
    while (temp != nullptr) {
      if (temp->key == clave) {
        return temp;
      }
      temp = temp->next;
    }
    return nullptr;
  }

  bool eliminar(K clave) {
    int idx = _hash(clave);
    Node<K, V> *temp = buckets[idx];
    Node<K, V> *prev = nullptr;
    while (temp != nullptr) {
      if (temp->key == clave) {
        if (prev == nullptr) {
          buckets[idx] = temp->next;
        } else {
          prev->next = temp->next;
        }
        delete temp;
        n--;
        return true;
      }
      prev = temp;
      temp = temp->next;
    }
    return false;
  }

  void imprimir() {
    for (int i = 0; i < m; i++) {
      cout << "[" << i << "]: ";
      Node<K, V> *temp = buckets[i];
      while (temp != nullptr) {
        cout << "(" << temp->key << "," << temp->value << ") ";
        temp = temp->next;
      }
      cout << "\n";
    }
  }
};

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

  void preorden(Nodo *x, vector<T> &v) const {
    if (x == nullptr) {
      return;
    }
    v.push_back(x->clave);
    preorden(x->izq, v);
    preorden(x->der, v);
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

  Nodo *buscar(const T &k) const { return buscar(raiz, k); }

  Nodo *minimo(Nodo *x) const {
    if (x == nullptr) {
      return nullptr;
    }
    while (x->izq != nullptr) {
      x = x->izq;
    }
    return x;
  }

  Nodo *maximo(Nodo *x) const {
    if (x == nullptr) {
      return nullptr;
    }
    while (x->der != nullptr) {
      x = x->der;
    }
    return x;
  }

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

  void imprimirInorder() const {
    inorder(raiz);
    std::cout << "\n";
  }

  vector<T> ver() const {
    vector<T> v;
    preorden(raiz, v);
    return v;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  Diccionary<vector<int>, int> grupo;
  int k = 0;
  vector<int> res;
  while (m--) {
    BST<int> arbol;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      arbol.insertar(x);
    }
    vector<int> t = arbol.ver();
    Node<vector<int>, int> *nodo = grupo.search(t);
    if (nodo == nullptr) {
      grupo.insertar(t, ++k);
      res.push_back(k);
    } else {
      res.push_back(nodo->value);
    }
  }
  cout << k << "\n";
  for (int c : res) {
    cout << c << " ";
  }
  cout << "\n";
  return 0;
}
