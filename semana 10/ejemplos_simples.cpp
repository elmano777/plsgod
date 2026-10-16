#include <iostream>
#include <string>
using namespace std;

int suma(int n) {
  if (n == 0) {
    return 0;
  }
  return n + suma(n - 1);
}

void generar(int pos, int n, string &actual) {
  if (pos == n) {
    cout << actual << "\n";
    return;
  }
  for (char c : {'0', '1'}) {
    if (c == '1' && pos > 0 && actual[pos - 1] == '1') {
      continue;
    }
    actual.push_back(c);
    generar(pos + 1, n, actual);
    actual.pop_back();
  }
}

int main() {
  cout << "suma(4) = " << suma(4) << "\n";

  cout << "cadenas de largo 3 sin dos 1 seguidos:\n";
  string actual;
  generar(0, 3, actual);
  return 0;
}
