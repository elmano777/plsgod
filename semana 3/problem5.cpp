#include <iostream>
#include <string>

using namespace std;

template <typename T> struct Node {
  T data;
  Node *next;
  Node *prev;
};

template <typename T> class DoubleLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  Node<T> *actual; // puntero al nodo actual
  int size;

public:
  DoubleLinkedList() {
    head = nullptr;
    tail = nullptr;
    actual = nullptr;
    size = 0;
  };

  // Constructor opcional para crear con un valor inicial
  DoubleLinkedList(T val) {
    head = new Node<T>{val, nullptr, nullptr};
    tail = head;
    actual = head;
    size = 1;
  }

  void push_back(T val) {
    Node<T> *temp = new Node<T>{val, nullptr, tail};
    if (tail == nullptr) { // lista vacía
      head = temp;
      tail = temp;
      actual = temp; // si es el primer nodo, actual apunta a él
    } else {
      tail->next = temp;
      tail = temp;
    }
    size++;
  }

  // Método para visitar una nueva URL (borra el historial forward y agrega al final)
  void visitar(T url) {
    // Borrar todos los nodos adelante del actual (desde actual->next hasta tail)
    Node<T> *temp = actual->next;
    while (temp != nullptr) {
      Node<T> *next = temp->next;
      delete temp;
      temp = next;
      size--;
    }
    // Ahora actual->next es nullptr, actual es el nuevo tail
    tail = actual;

    // Crear nuevo nodo y insertarlo después de actual
    Node<T> *nuevo = new Node<T>{url, nullptr, actual};
    actual->next = nuevo;
    tail = nuevo; // el nuevo nodo se vuelve el tail
    actual = nuevo; // el actual se mueve al nuevo nodo
    size++;
  }

  // Retroceder 'pasos' posiciones (hacia atrás usando prev)
  void retroceder(int pasos) {
    for (int i = 0; i < pasos && actual->prev != nullptr; i++) {
      actual = actual->prev;
    }
    cout << actual->data << endl;
  }

  // Avanzar 'pasos' posiciones (hacia adelante usando next)
  void avanzar(int pasos) {
    for (int i = 0; i < pasos && actual->next != nullptr; i++) {
      actual = actual->next;
    }
    cout << actual->data << endl;
  }

  // Imprimir el historial completo, marcando el actual
  void historial() {
    Node<T> *temp = head;
    while (temp != nullptr) {
      if (temp == actual) {
        cout << "[" << temp->data << "]";
      } else {
        cout << temp->data;
      }
      if (temp->next != nullptr) {
        cout << " ";
      }
      temp = temp->next;
    }
    cout << endl;
  }

  // Destructor (heredado de la implementación anterior, pero actualizado para incluir 'actual')
  ~DoubleLinkedList() {
    Node<T> *temp = head;
    while (temp) {
      Node<T> *next = temp->next;
      delete temp;
      temp = next;
    }
    head = nullptr;
    tail = nullptr;
    actual = nullptr;
    size = 0;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  // Inicializar el historial con la página de inicio
  DoubleLinkedList<string> historial;
  historial.push_back("inicio");

  while (n--) {
    string op;
    cin >> op;
    if (op == "VISITAR") {
      string url;
      cin >> url;
      historial.visitar(url);
    } else if (op == "RETROCEDER") {
      int k;
      cin >> k;
      historial.retroceder(k);
    } else if (op == "AVANZAR") {
      int k;
      cin >> k;
      historial.avanzar(k);
    } else if (op == "HISTORIAL") {
      historial.historial();
    }
  }

  return 0;
}