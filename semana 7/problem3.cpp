#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T> class MinHeap {
private:
  vector<T> H;
  int n;
  int contador;

  int padre(int i) const { return i / 2; }
  int izq(int i) const { return 2 * i; }
  int der(int i) const { return 2 * i + 1; }

  void siftUp(int i) {
    T valor = H[i];
    while (i > 1 && H[padre(i)] > valor) {
      H[i] = H[padre(i)];
      i = padre(i);
    }
    H[i] = valor;
  }

  void siftDown(int i) {
    while (izq(i) <= n) {
      int menor = izq(i);
      if (der(i) <= n && H[der(i)] < H[izq(i)]) {
        menor = der(i);
      }
      if (H[menor] < H[i]) {
        swap(H[i], H[menor]);
        i = menor;
        contador++;
      } else {
        break;
      }
    }
  }

public:
  MinHeap() : H(1), n(0), contador(0) {}

  T cont() const { return contador; }

  T top() const { return H[1]; }

  void insertar(const T &x) {
    H.push_back(x);
    n++;
    siftUp(n);
  }

  T extraerExtremo() {
    if (n == 0) {
      throw out_of_range("heap vacío");
    }
    T resultado = H[1];
    H[1] = H[n];
    H.pop_back();
    n--;
    if (n > 0) {
      siftDown(1);
    }
    return resultado;
  }

  int size() const { return n; }

  void construirHeap(const vector<T> &arreglo) {
    n = static_cast<int>(arreglo.size());
    H.assign(1, T());
    H.insert(H.end(), arreglo.begin(), arreglo.end());
    for (int i = n / 2; i >= 1; i--) {
      siftDown(i);
    }
  }

  void heapsort(vector<T> &arreglo) {
    construirHeap(arreglo);
    int m = n;
    for (int i = 0; i < m - 1; i++) {
      swap(H[1], H[n]);
      n--;
      siftDown(1);
    }
    for (int k = 0; k < m; k++) {
      arreglo[k] = H[m - k];
    }
    n = 0;
  }

  void imprimir() {
    for (size_t i = 1; i < H.size(); i++) {
      cout << H[i] << (i + 1 < H.size() ? " " : "");
    }
    cout << endl;
  }
};

int main() {
  MinHeap<int> heap;
  int n;
  cin >> n;
  vector<int> arreglo(n);
  for (int i = 0; i < n; i++) {
    cin >> arreglo[i];
  }
  heap.construirHeap(arreglo);
  cout << heap.cont() << endl;
  heap.imprimir();
  return 0;
}
