#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> tab(9);
bool fil[9][10], col[9][10], cuad[9][10]; // [fila/col/cuadrante][dígito]

// Rellena las casillas desde la posición pos (0..80). Devuelve true si logra
// completar el tablero.
bool resolver(int pos) {
  if (pos == 81) {
    return true;
  }
  int f = pos / 9, c = pos % 9;
  if (tab[f][c] != '.') {
    return resolver(pos + 1); // casilla ya llena
  }
  int q = (f / 3) * 3 + c / 3;
  for (int d = 1; d <= 9; d++) {
    if (fil[f][d] || col[c][d] || cuad[q][d]) {
      continue;
    }
    tab[f][c] = '0' + d;
    fil[f][d] = col[c][d] = cuad[q][d] = true; // agregar
    if (resolver(pos + 1)) {                   // explorar
      return true;
    }
    fil[f][d] = col[c][d] = cuad[q][d] = false; // quitar
    tab[f][c] = '.';
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  for (int i = 0; i < 9; i++) {
    cin >> tab[i];
  }
  for (int f = 0; f < 9; f++) {
    for (int c = 0; c < 9; c++) {
      if (tab[f][c] != '.') {
        int d = tab[f][c] - '0';
        fil[f][d] = col[c][d] = cuad[(f / 3) * 3 + c / 3][d] = true;
      }
    }
  }
  resolver(0);
  for (int i = 0; i < 9; i++) {
    cout << tab[i] << "\n";
  }
  return 0;
}
