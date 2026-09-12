#include <iostream>
#include <vector>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
};

template <typename T> class Stack {
private:
  Node<T> *top_;
  int size;

public:
  Stack() {
    top_ = nullptr;
    size = 0;
  }

  ~Stack() {
    Node<T> *temp = top_;
    while (temp != nullptr) {
      Node<T> *next = temp->next;
      delete temp;
      temp = next;
    }
    top_ = nullptr;
    size = 0;
  }

  void push(T x) {
    Node<T> *x_ = new Node<T>{x, top_};
    top_ = x_;
    size++;
  }

  void pop() {
    if (size == 0) {
      return;
    }
    Node<T> *temp = top_;
    top_ = top_->next;
    delete temp;
    size--;
  }

  T top() { return top_->data; }

  bool empty() { return size == 0; }
};

int leerPila(int n, Stack<int> &st) {
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int suma = 0;
  for (int i = n - 1; i >= 0; i--) {
    st.push(a[i]);
    suma += a[i];
  }
  return suma;
}

int main() {
  int n1, n2, n3;
  cin >> n1 >> n2 >> n3;
  Stack<int> st1, st2, st3;
  int sum1 = leerPila(n1, st1);
  int sum2 = leerPila(n2, st2);
  int sum3 = leerPila(n3, st3);
  while (!(sum1 == sum2 && sum2 == sum3)) {
    if (sum1 >= sum2 && sum1 >= sum3) {
      sum1 -= st1.top();
      st1.pop();
    } else if (sum2 >= sum1 && sum2 >= sum3) {
      sum2 -= st2.top();
      st2.pop();
    } else {
      sum3 -= st3.top();
      st3.pop();
    }
  }
  cout << sum1 << endl;
  return 0;
}
