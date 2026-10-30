#include <iostream>
#include <string>

using namespace std;

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

  generar(0, 3, actual);
  return 0;
}
