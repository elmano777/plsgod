#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  vector<long long> N;
  N.push_back(1);
  N.push_back(2);
  while (N.back() <= 1e18) {
    N.push_back(N[N.size() - 1] + N[N.size() - 2] + 1);
  }
  while (t--) {
    long long n;
    cin >> n;
    int maxima = 0;
    for (int h = 0; h < N.size(); h++) {
      if (N[h] <= n) {
        maxima = h;
      } else {
        break;
      }
    }
    int minima = 0;
    while ((1LL << (minima + 1)) - 1 < n) {
      minima++;
    }
    cout << minima << " " << maxima << "\n";
  }
  return 0;
}
