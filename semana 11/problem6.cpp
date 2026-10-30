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
    int u, v;
    cin >> u >> v;
    vector<int> comunes;
    set_intersection(adj[u].begin(), adj[u].end(), adj[v].begin(), adj[v].end(),
                     back_inserter(comunes));
    cout << comunes.size() << '\n';
  }
  return 0;
}
