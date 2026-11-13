#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }
  for (int u = 1; u <= n; u++) {
    sort(adj[u].begin(), adj[u].end());
  }
  vector<int> estado(n + 1, 0);
  vector<int> tin(n + 1, 0);
  vector<int> idx(n + 1, 0);
  int tiempo = 0;
  long long arbol = 0, retroceso = 0, avance = 0, cruce = 0;
  for (int r = 1; r <= n; r++) {
    if (estado[r] != 0) {
      continue;
    }
    stack<int> pil;
    pil.push(r);
    estado[r] = 1;
    tin[r] = tiempo++;
    while (!pil.empty()) {
      int u = pil.top();
      if (idx[u] < (int)adj[u].size()) {
        int v = adj[u][idx[u]];
        idx[u]++;
        if (estado[v] == 0) {
          arbol++;
          estado[v] = 1;
          tin[v] = tiempo++;
          pil.push(v);
        } else if (estado[v] == 1) {
          retroceso++;
        } else if (tin[u] < tin[v]) {
          avance++;
        } else {
          cruce++;
        }
      } else {
        estado[u] = 2;
        pil.pop();
      }
    }
  }
  cout << arbol << " " << retroceso << " " << avance << " " << cruce << "\n";
  return 0;
}
