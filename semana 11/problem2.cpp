#include <iostream>
#include <vector>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<int> deg(n + 1, 0);
  while (m--) {
    int u, v;
    cin >> u >> v;
    deg[u]++;
    deg[v]++;
  }
  int par = 0;
  for (int i = 1; i <= n; i++) {
    if (deg[i] % 2 == 1) {
      par++;
    }
  }
  if (par == 0) {
    cout << "CIRCUITO" << endl;
  } else if (par == 2) {
    cout << "CAMINO" << endl;
  } else {
    cout << "IMPOSIBLE" << endl;
  }
  return 0;
}
