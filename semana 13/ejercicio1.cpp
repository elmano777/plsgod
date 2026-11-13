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
  int n, m;
  cin >> n >> m;
  vector<string> is(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char ag;
      cin >> ag;
      is[i].push_back(ag);
    }
  }
  array<int, 4> dx = {1, -1, 0, 0};
  array<int, 4> dy = {0, 0, 1, -1};
  int islas = 0;
  int mayor = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (is[i][j] == '#') {
        islas++;
        int tam = 0;
        stack<pair<int, int>> pos;
        pos.push({i, j});
        is[i][j] = '.';
        while (!pos.empty()) {
          pair<int, int> posac = pos.top();
          pos.pop();
          tam++;
          for (int k = 0; k < 4; k++) {
            int nx = posac.first + dx[k];
            int ny = posac.second + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
              continue;
            }
            if (is[nx][ny] == '#') {
              is[nx][ny] = '.';
              pos.push({nx, ny});
            }
          }
        }
        mayor = max(mayor, tam);
      }
    }
  }
  cout << islas << " " << mayor << endl;
  return 0;
}
