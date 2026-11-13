#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool col[10], diag1[20], diag2[20];

// Devuelve cuántas formas hay de colocar reinas desde "fila" hasta n-1
int resolver(int fila, int n, vector<string> &tab) {
  if (fila == n) {
    return 1; // las n reinas quedaron bien colocadas
  }
  int total = 0;
  for (int c = 0; c < n; c++) {
    if (tab[fila][c] == '#' || col[c] || diag1[fila + c] ||
        diag2[fila - c + n - 1]) {
      continue;
    }
    col[c] = diag1[fila + c] = diag2[fila - c + n - 1] = true; // agregar
    total += resolver(fila + 1, n, tab);                       // explorar
    col[c] = diag1[fila + c] = diag2[fila - c + n - 1] = false; // quitar
  }
  return total;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<string> tab(n);
  for (int i = 0; i < n; i++) {
    cin >> tab[i];
  }
  cout << resolver(0, n, tab) << "\n";
  return 0;
}
