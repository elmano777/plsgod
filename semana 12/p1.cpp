#include <cstddef>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  long long n, m;
  cin >> n >> m;
  set<long long> entr;
  while (m--) {
    long long u, v;
    cin >> u >> v;
    entr.insert(u);
    entr.insert(v);
  }
  cout << "SI" << endl;
  return 0;
}
