#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<int> clave(n + 1), izq(n + 1), der(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> clave[i] >> izq[i] >> der[i];
    }

    bool esBST = true;
    long long anterior = -1;
    vector<int> pila;
    int actual = 1;
    while (actual != 0 || !pila.empty()) {
      while (actual != 0) {
        pila.push_back(actual);
        actual = izq[actual];
      }
      actual = pila.back();
      pila.pop_back();
      if (clave[actual] <= anterior) {
        esBST = false;
        break;
      }
      anterior = clave[actual];
      actual = der[actual];
    }

    if (!esBST) {
      cout << "NINGUNO\n";
      continue;
    }

    vector<int> orden;
    orden.reserve(n);
    queue<int> cola;
    cola.push(1);
    while (!cola.empty()) {
      int v = cola.front();
      cola.pop();
      orden.push_back(v);
      if (izq[v]) cola.push(izq[v]);
      if (der[v]) cola.push(der[v]);
    }

    vector<int> altura(n + 1);
    altura[0] = -1;
    bool esAVL = true;
    for (int i = n - 1; i >= 0; i--) {
      int v = orden[i];
      int hi = altura[izq[v]];
      int hd = altura[der[v]];
      altura[v] = 1 + max(hi, hd);
      if (abs(hi - hd) > 1) {
        esAVL = false;
      }
    }

    cout << (esAVL ? "AVL" : "BST") << "\n";
  }
  return 0;
}
