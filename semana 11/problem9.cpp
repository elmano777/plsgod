#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, L;
  cin >> n >> L;

  vector<string> w(n);
  for (int i = 0; i < n; i++)
    cin >> w[i];

  vector<int> deg(n, 0);
  long long aristas = 0;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int dif = 0;
      for (int k = 0; k < L && dif <= 1; k++) {
        if (w[i][k] != w[j][k])
          dif++;
      }
      if (dif == 1) {
        aristas++;
        deg[i]++;
        deg[j]++;
      }
    }
  }

  int maxDeg = *max_element(deg.begin(), deg.end());
  int aisladas = count(deg.begin(), deg.end(), 0);

  cout << aristas << " " << maxDeg << " " << aisladas << '\n';
  return 0;
}
