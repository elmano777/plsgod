#include <iostream>
#include <vector>

using namespace std;

template <typename K, typename V> struct Node {
  K key;
  V value;
  Node *next;
  Node(K k, V v, Node *nex = nullptr) : key(k), value(v), next(nex) {}
};

template <typename K, typename V> class Diccionary {
private:
  vector<Node<K, V> *> buckets;
  int n;
  int m;
  long long _hashRaw(K clave) {
    const long long B = 311;
    const long long MOD = 1e9 + 7;
    long long hash_value = 0;
    K key = clave;
    while (key > 0) {
      int d = key % 10;
      hash_value = (hash_value * B + (d + 1)) % MOD;
      key /= 10;
    }
    return hash_value;
  }
  int _hash(K clave) { return (int)(_hashRaw(clave) % m); }

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
        int idxNuevo = (int)(_hashRaw(actual->key) % m_nuevo);
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

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Diccionary<int, int> d;
  int n, m;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int na;
    cin >> na;
    Node<int, int> *temp = d.search(na);
    if (temp) {
      temp->value += 1;
    } else {
      d.insertar(na, 1);
    }
  }
  cin >> m;
  if (n != m) {
    cout << "NO" << endl;
    return 0;
  }
  for (int i = 0; i < m; i++) {
    int ma;
    cin >> ma;
    Node<int, int> *temp = d.search(ma);
    if (temp == nullptr) {
      cout << "NO" << endl;
      return 0;
    }
    temp->value -= 1;
    if (temp->value < 0) {
      cout << "NO" << endl;
      return 0;
    }
  }
  cout << "SI" << endl;
  return 0;
}
