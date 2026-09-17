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

template <> long long hashRaw<long long>(long long clave) {
  const long long B = 311;
  const long long MOD = 1e9 + 7;
  long long hash_value = 0;
  long long key = clave < 0 ? -clave : clave;
  if (key == 0)
    return 1;
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
  };

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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<long long> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  Diccionary<long long, int> frecuencias;
  long long prefix = 0;
  int maxFrecuencia = 0;
  for (int i = 0; i < n; i++) {
    prefix += a[i];
    Node<long long, int> *actual = frecuencias.search(prefix);
    int nuevaFrecuencia;
    if (actual) {
      actual->value += 1;
      nuevaFrecuencia = actual->value;
    } else {
      frecuencias.insertar(prefix, 1);
      nuevaFrecuencia = 1;
    }
    if (nuevaFrecuencia > maxFrecuencia) {
      maxFrecuencia = nuevaFrecuencia;
    }
  }
  cout << (n - maxFrecuencia) << endl;
  return 0;
}
