#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n + 1);
  vector<vector<char>> es(n + 1, vector<char>(n + 1, 0));

  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    es[a][b] = es[b][a] = 1;
  }

  long long trios = 0;
  for (int a = 1; a <= n; a++) {
    for (int b : adj[a]) {
      if (b <= a)
        continue;
      for (int c : adj[b]) {
        if (c <= b)
          continue;
        if (es[a][c])
          trios++;
      }
    }
  }

  cout << trios << '\n';
  return 0;
}
