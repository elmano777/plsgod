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

// hashRaw generico: sin cuerpo, solo se puede usar a traves de una
// especializacion explicita (una por cada tipo de clave soportado)
template <typename T> long long hashRaw(T clave);

// especializacion para claves enteras: metodo posicional sobre los digitos
template <> long long hashRaw<int>(int clave) {
  const long long B = 311;
  const long long MOD = 1e9 + 7;
  long long hash_value = 0;
  int key = clave < 0 ? -clave : clave; // valor absoluto: negativos no rompen el while
  while (key > 0) {
    int d = key % 10;
    hash_value = (hash_value * B + (d + 1)) % MOD;
    key /= 10;
  }
  return hash_value;
}

// especializacion para claves string: hashing polinomial sobre los caracteres
// B > tamano del alfabeto (ascii ~128, usamos 131 como es usual)
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
    // O(m_viejo + n) -- se paga una vez cada vez que se duplica, amortizado
    // O(1) por insercion
    int m_nuevo = siguientePrimo(2 * m);
    vector<Node<K, V> *> bucketsNuevos(m_nuevo, nullptr);
    for (int i = 0; i < m; i++) {
      Node<K, V> *actual = buckets[i];
      while (actual != nullptr) {
        Node<K, V> *siguiente =
            actual->next; // guardar antes de mover el puntero
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
        return; // clave existente: actualizar y salir, no insertar nodo
      }
      temp = temp->next;
    }
    // clave nueva: recien aca chequeamos factor de carga
    if ((double)(n + 1) / m >= 0.75) {
      rehash();
      idx = _hash(clave); // recalcular con el m nuevo
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
          buckets[idx] = temp->next; // borrando la cabeza del bucket
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
    return false; // no encontrada
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
  Diccionary<int, int> d;
  for (int i = 1; i <= 15; i++) d.insertar(i, i * 10);
  d.imprimir();
  cout << (d.search(7) ? "encontrado" : "no encontrado") << "\n";
  d.eliminar(7);
  cout << (d.search(7) ? "encontrado" : "no encontrado") << "\n";

  cout << "--- prueba con negativos y cero ---\n";
  Diccionary<int, int> d2;
  d2.insertar(0, 100);
  d2.insertar(-1, 200);
  d2.insertar(-500, 300);
  d2.insertar(999999999, 400);
  d2.insertar(-999999999, 500);
  d2.imprimir();
  cout << (d2.search(-500) ? "encontrado -500" : "no encontrado -500") << "\n";
  cout << (d2.search(0) ? "encontrado 0" : "no encontrado 0") << "\n";
  d2.eliminar(-500);
  cout << (d2.search(-500) ? "encontrado -500" : "no encontrado -500") << "\n";

  cout << "--- prueba con string (conteo de palabras) ---\n";
  Diccionary<string, int> d3;
  vector<string> palabras = {"el", "gato", "come", "y", "el", "perro", "come"};
  for (const string &w : palabras) {
    Node<string, int> *nodo = d3.search(w);
    if (nodo) {
      nodo->value += 1;
    } else {
      d3.insertar(w, 1);
    }
  }
  d3.imprimir();
  return 0;
}
