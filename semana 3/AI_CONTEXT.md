# AI Context — semana 3

> Contexto específico para los archivos de esta carpeta. Se complementa
> con `../AI_CONTEXT.md` (raíz) y con la nota del vault
> `Utec 6to/AED/AED.md` — **leelos primero**.

## Tema de la semana

**Listas — Estructuras de Datos Lineales Parte 1** (semana 3 del sílabo).
Material del **profe Víctor Racsó Galván Oyola** (`vgalvan@utec.edu.pe`),
no de Luciano. Se conserva como material de apoyo; el `Resumen.md` en el
vault lleva un callout avisándolo. Si Luciano sube material propio de
semana 3, contrastar y reubicar.

El temario cubre: listas simplemente enlazadas, doblemente enlazadas y
circulares; implementación manual en C++; iteradores; matrices esparsas.

## Qué hay en esta carpeta

| Archivo | Qué es |
|---|---|
| `linkedlist.cpp` | **Archivo vacío** (0 bytes). Placeholder esperando la primera implementación. |

Eso es todo por ahora. La semana recién empieza.

## Convenciones esperadas

- **Lenguaje:** C++ (g++ con `-std=c++17`, idealmente `-O2`).
- **No usar `std::list`** de la STL para las entregas: la idea es
  implementar la estructura a mano (nodos con `next` / `prev`).
- Cada TDA en su propio `.cpp` o, si crece, en `linkedlist.hpp` +
  `main.cpp` de prueba. Preguntar al usuario antes de partir en
  varios archivos.
- Documentar en comentarios la **complejidad** de cada operación
  (`push_front`, `push_back`, `pop_front`, `find`, `insert`, `remove`,
  etc.) — es parte del curso.

## Plan sugerido (a confirmar con el usuario)

1. **Lista simplemente enlazada** (SinglyLinkedList) con `head` y
   `tail` opcionales; operaciones básicas + destructor.
2. **Lista doblemente enlazada** (DoublyLinkedList) con `head` y
   `tail`; las mismas operaciones + recorrido inverso.
3. **Lista circular** (simple o doble, a decidir) — útil para buffer
   ring / scheduling.
4. **Matriz esparsa** con listas de listas (bonus si hay tiempo).
5. Tests rápidos en `main()` antes de considerar "listo".

## Reglas de la IA para esta carpeta

1. **Preguntar antes de crear archivos.** El usuario puede preferir
   un solo `linkedlist.cpp` con todo, o separarlo en `singly/`,
   `doubly/`, `circular/`. No asumir.
2. **No uses `std::list`**, `std::forward_list` ni `std::vector` para
   almacenar los nodos. Sí se vale usarlos **temporalmente** en tests.
3. **Siempre incluir el destructor.** Las singly/doubly olvidadizas
   con `new` sin `delete` son un bug clásico de AED; la IA debe
   chequearlo.
4. **Complejidad en comentarios** (`// O(1)`, `// O(n)`, etc.) en cada
   método público.
5. **Compilar y correr** los tests antes de devolver. Si `main()`
   trakea con asserts, mejor.
6. **No mezcles material de Víctor con el de Luciano** sin avisar.
   Si el `Resumen.md` del vault cita a Luciano y este código sale de
   las slides de Víctor, mencionalo en el comentario de cabecera.

---

**Mantenido por:** Rola · CS2023 semana 3 · UTEC 2026-2
