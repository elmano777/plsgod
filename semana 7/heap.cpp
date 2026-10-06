#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T> class MinHeap {
private:
  vector<T> H; // 1-indexado: H[0] sin usar
  int n;

  int padre(int i) const { return i / 2; }
  int izq(int i) const { return 2 * i; }
  int der(int i) const { return 2 * i + 1; }

  // O(lg n)
  void siftUp(int i) {
    T valor = H[i];
    while (i > 1 && H[padre(i)] > valor) {
      H[i] = H[padre(i)];
      i = padre(i);
    }
    H[i] = valor;
  }

  // O(lg n)
  void siftDown(int i) {
    while (izq(i) <= n) {
      int menor = izq(i);
      if (der(i) <= n && H[der(i)] < H[izq(i)]) {
        menor = der(i);
      }
      if (H[menor] < H[i]) {
        std::swap(H[i], H[menor]);
        i = menor;
      } else {
        break;
      }
    }
  }

public:
  MinHeap() : H(1), n(0) {} // H[0] de relleno

  // O(1)
  T top() const { return H[1]; }

  // O(lg n)
  void insertar(const T &x) {
    H.push_back(x);
    n++;
    siftUp(n);
  }

  // O(lg n)
  T extraerExtremo() {
    if (n == 0) {
      throw std::out_of_range("heap vacío");
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

  // O(1)
  int size() const { return n; }

  // O(n)
  void construirHeap(const std::vector<T> &arreglo) {
    n = static_cast<int>(arreglo.size());
    H.assign(1, T()); // H[0] de relleno
    H.insert(H.end(), arreglo.begin(), arreglo.end());
    for (int i = n / 2; i >= 1; i--) {
      siftDown(i);
    }
  }

  // O(n lg n), in-place
  // Decisión: seguimos usando el MIN-heap que ya tenemos (no hace falta
  // implementar uno de máximos aparte). Al intercambiar la raíz con el
  // último elemento activo y reducir el heap, los mínimos van quedando
  // "congelados" en las últimas posiciones en orden DESCENDENTE
  // (el más chico al final, el más grande en H[1] al terminar). Para
  // dejar `arreglo` en orden creciente, volcamos H leyéndolo al revés.
  void heapsort(std::vector<T> &arreglo) {
    construirHeap(arreglo);
    int m = n;
    for (int i = 0; i < m - 1; i++) {
      std::swap(H[1], H[n]);
      n--;
      siftDown(1);
    }
    for (int k = 0; k < m; k++) {
      arreglo[k] = H[m - k];
    }
    n = 0;
  }
};

int main() {
  // Ejemplo de la clase: H = [2, 4, 3, 8, 6, 9, 7] es un min-heap válido
  MinHeap<int> heap;
  vector<int> x;
  x.push_back(1);

  return 0;
}
