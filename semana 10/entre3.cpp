// repo https://github.com/elmano777/plsgod.git

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void generar(int pos, int n, string &actual) {
  if (pos == n) {
    cout << actual << "\n";
    return;
  }
  for (char c : {'0', '1'}) {
    if (c == '1' && pos > 0 && actual[pos - 1] == '1') {
      continue;
    }
    actual.push_back(c);
    generar(pos + 1, n, actual);
    actual.pop_back();
  }
}

int camino(size_t pos, size_t n, vector<vector<char>> pas) {
  if (pos == n) {
    return 1;
  }
  for (char c : {'0', '1'}) {
    if (c == '1' && pos > 0 && actual[pos - 1] == '1') {
      continue;
    }
    actual.push_back(c);
    generar(pos + 1, n, actual);
    actual.pop_back();
  }
  int rpta;
  for (size_t i; i < pas.size(); i++) {
    for (size_t j; j < pas[i].size(); i++) {
      for (auto c : pas[i]) {
        if (c == '.' && pos > 0 && actual[pos - 1] == '1') {
          continue;
        }
      }
    }
  }
  return rpta;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int x;
  cin >> x;
  vector<vector<char>> en(x);
  int y;
  cin >> y;
  while (x--) {
    vector<char> rell(y);
    for (int i = 0; i < y; i++) {
      char op;
      cin >> op;
      rell.push_back(op);
    }
  }
  return 0;
}
