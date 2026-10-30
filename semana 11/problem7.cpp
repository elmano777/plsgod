#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int A, B, x, y;
  cin >> A >> B >> x >> y;
  long long aristas = 0;
  long long entrada = 0;
  for (int a = 0; a <= A; a++) {
    for (int b = 0; b <= B; b++) {
      int t1 = min(a, B - b);
      int t2 = min(b, A - a);
      pair<int, int> dest[6] = {
          {A, b},
          {a, B},
          {0, b},
          {a, 0},
          {a - t1, b + t1},
          {a + t2, b - t2},
      };
      sort(dest, dest + 6);
      int distintos = 0;
      bool llega = false;
      for (int i = 0; i < 6; i++) {
        if (i > 0 && dest[i] == dest[i - 1])
          continue;
        if (dest[i] == make_pair(a, b))
          continue;
        distintos++;
        if (dest[i] == make_pair(x, y))
          llega = true;
      }
      aristas += distintos;
      if (llega)
        entrada++;
    }
  }
  cout << aristas << " " << entrada << '\n';
  return 0;
}
