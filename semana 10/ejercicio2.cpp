#include <iostream>

using namespace std;

void hanoi(int n, int a, int b, int c) {
  if (n == 0) return;
  hanoi(n - 1, a, c, b);
  cout << n << " " << a << " " << c << "\n";
  hanoi(n - 1, b, a, c);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  hanoi(n, 1, 2, 3);
  return 0;
}
