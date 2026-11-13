#include <algorithm>
#include <array>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<int> tin(n + 1);
  vector<int> tout(n + 1);
  int tiempo = 0;
  vector<int> pa(n + 1, 0);
  vector<int> idx(n + 1, 0);
  stack<int> pil;
  pil.push(1);
  tin[1] = tiempo;
  tiempo++;
  while (!pil.empty()) {
    int u = pil.top();
    if (idx[u] < (int)adj[u].size()) {
      int w = adj[u][idx[u]];
      idx[u]++;
      if (w == pa[u]) {
        continue;
      }
      pa[w] = u;
      tin[w] = tiempo;
      tiempo++;
      pil.push(w);
    } else {
      tout[u] = tiempo;
      pil.pop();
    }
  }
  for (int i = 0; i < q; i++) {
    int u, v;
    cin >> u >> v;
    if (tin[u] <= tin[v] && tout[v] <= tout[u]) {
      cout << "SI" << "\n";
    } else {
      cout << "NO" << "\n";
    }
  }
  return 0;
}
