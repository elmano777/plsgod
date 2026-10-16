#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> izq(n + 1), der(n + 1), padre(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> izq[i] >> der[i];
    if (izq[i]) padre[izq[i]] = i;
    if (der[i]) padre[der[i]] = i;
  }
  int raiz = 1;

  while (q--) {
    char tipo;
    int x;
    cin >> tipo >> x;
    int p = padre[x];

    if (tipo == 'I') {
      int y = der[x];
      der[x] = izq[y];
      if (izq[y]) padre[izq[y]] = x;
      izq[y] = x;
      padre[x] = y;
      padre[y] = p;
      if (p == 0) {
        raiz = y;
      } else if (izq[p] == x) {
        izq[p] = y;
      } else {
        der[p] = y;
      }
    } else {
      int y = izq[x];
      izq[x] = der[y];
      if (der[y]) padre[der[y]] = x;
      der[y] = x;
      padre[x] = y;
      padre[y] = p;
      if (p == 0) {
        raiz = y;
      } else if (izq[p] == x) {
        izq[p] = y;
      } else {
        der[p] = y;
      }
    }
  }

  cout << raiz << "\n";
  for (int i = 1; i <= n; i++) {
    cout << izq[i] << " " << der[i] << "\n";
  }
  return 0;
}
