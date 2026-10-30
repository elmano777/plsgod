#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, m, q;
  cin >> n >> m >> q;
  vector<vector<int>> adj(n + 1);
  while (m--) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    sort(adj[i].begin(), adj[i].end());
  }
  while (q--) {
    int c;
    cin >> c;
    if (c == 1) {
      int a, b;
      cin >> a >> b;
      if (adj[a].size() < b) {
        cout << "-1" << "\n";
      } else {
        cout << adj[a][b - 1] << "\n";
      }
    } else {
      int a, b;
      cin >> a >> b;
      int mayor = upper_bound(adj[a].begin(), adj[a].end(), b) - adj[a].begin();
      cout << mayor << "\n";
    }
  }
  return 0;
}
