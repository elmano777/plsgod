#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> ve;
int pos = 0;

long long eval() {
  string tok = ve[pos++];
  if (tok != "+" && tok != "-" && tok != "*") {
    return stoll(tok); // caso base: es un número
  }
  long long a = eval(); // operando izquierdo
  long long b = eval(); // operando derecho
  if (tok == "+")
    return a + b;
  if (tok == "-")
    return a - b;
  return a * b;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int m;
  cin >> m;
  ve.resize(m);
  for (int i = 0; i < m; i++)
    cin >> ve[i];
  cout << eval() << "\n";
  return 0;
}
