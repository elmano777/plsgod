#include <iostream>
using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
  Node *prev;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  if (n == 0) { return 0; }
  if (n == 1) { cout << 1 << endl; return 0; }

  Node<int> *head = new Node<int>{1, nullptr, nullptr};
  Node<int> *cur = head;
  for (int i = 2; i <= n; i++) {
    Node<int> *nn = new Node<int>{i, nullptr, nullptr};
    cur->next = nn;
    nn->prev = cur;
    cur = nn;
  }
  cur->next = head;
  head->prev = cur;

  Node<int> *temp = head->next;
  int remaining = n;
  while (remaining > 1) {
      cout << temp->data << " ";
      Node<int> *toDelete = temp;
      toDelete->prev->next = toDelete->next;
      toDelete->next->prev = toDelete->prev;
      Node<int> *nextNode = toDelete->next->next;
      delete toDelete;
      remaining--;
      temp = nextNode;
  }
  cout << temp->data << endl;
  return 0;
}
