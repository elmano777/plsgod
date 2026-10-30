#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> adj(n + 1, 0);
  map<pair<int, int>, int> cnt;
  while (m--) {
    int u, v;
    cin >> u >> v;
    if (u > v) {
      swap(u, v);
    }
    cnt[{u, v}]++;
  }
  while (q--) {
    int u, v;
    cin >> u >> v;
    if (u > v) {
      swap(u, v);
    }
    cout << cnt[{u, v}] << '\n';
  }
  return 0;
}
