#include <iostream>
#include <string>

using namespace std;

void generar(string cad, int abiertos, int cerrados, int n) {
  if (cad.size() == 2 * n) {
    cout << cad << "\n";
    return;
  }
  if (abiertos < n) {
    generar(cad + '(', abiertos + 1, cerrados, n);
  }
  if (cerrados < abiertos) {
    generar(cad + ')', abiertos, cerrados + 1, n);
  }
}

int main() {
  int n;
  cin >> n;
  generar("", 0, 0, n);
  return 0;
}
