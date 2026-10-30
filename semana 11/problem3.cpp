#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<int> segui(n + 1, 0);
  set<pair<int, int>> rel;
  while (m--) {
    int a, b;
    cin >> a >> b;
    segui[b]++;
    rel.insert({a, b});
  }
  int mutuos = 0;
  for (auto [a, b] : rel) {
    if (a < b && rel.count({b, a})) {
      mutuos++;
    }
  }
  int mejor = max_element(segui.begin() + 1, segui.end()) - segui.begin();
  cout << mutuos << " " << mejor << " " << segui[mejor] << endl;
  return 0;
}
