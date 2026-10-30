#include <ios>
#include <iostream>

using namespace std;

int contar(int i, int suma, int n, int S, int a[20]) {
  if (i == n) {
    return suma == S ? 1 : 0;
  }
  return contar(i + 1, suma, n, S, a) + contar(i + 1, suma + a[i], n, S, a);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, S;
  cin >> n;
  cin >> S;
  int a[20];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  cout << contar(0, 0, n, S, a) << "\n";
  return 0;
}
