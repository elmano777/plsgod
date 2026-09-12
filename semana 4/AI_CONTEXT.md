# AI Context — semana 4

> Contexto específico para los archivos de esta carpeta. Se complementa
> con `../AI_CONTEXT.md` (raíz) y con la nota del vault
> `Utec 6to/AED/AED.md` — **leelos primero**.

## Tema de la semana

**Pilas, Colas y Colas dobles (Deques)** — Estructuras de Datos Lineales
Parte 2 (semana 4 del sílabo). Material del **profe Víctor Racsó Galván
Oyola** (`vgalvan@utec.edu.pe`), no de Luciano. Mismo tratamiento que
semana 3: material de apoyo de otra sección mientras llega el oficial.

**PDF de la clase (leer si hace falta más detalle o ejemplos):**
`/home/rola/Documents/Obsidian Vault/Utec 6to/AED/Semana 4/Sem4_Pilas_Colas_Colas_dobles.pdf`
(resumen ya hecho en el vault: `Utec 6to/AED/Semana 4/Resumen.md`).

## Qué toca implementar

La clase fue teoría pura (la implementación se prometió para "la próxima
clase" — o sea, ahora). Los tres TDA a implementar **a mano** (sin
`std::stack`, `std::queue` ni `std::deque` de la STL):

### 1. Pila (Stack) — LIFO
| Operación | Efecto | Complejidad exigida |
|---|---|---|
| `push(x)` | agrega `x` en el tope | O(1) |
| `pop()` | quita el elemento del tope | O(1) |
| `top()` | consulta (sin quitar) el tope | O(1) |
| `empty()` | ¿está vacía? | O(1) |

### 2. Cola (Queue) — FIFO
| Operación | Efecto | Complejidad exigida |
|---|---|---|
| `enqueue(x)` | agrega `x` al final | O(1) |
| `dequeue()` | quita el elemento del frente | O(1) |
| `front()` | consulta (sin quitar) el frente | O(1) |
| `empty()` | ¿está vacía? | O(1) |

### 3. Cola doble (Deque)
| Operación | Efecto | Complejidad exigida |
|---|---|---|
| `push_front(x)` | agrega `x` al inicio | O(1) |
| `push_back(x)` | agrega `x` al final | O(1) |
| `pop_front()` | quita del inicio | O(1) |
| `pop_back()` | quita del final | O(1) |

Las cuatro operaciones de cada TDA deben ser **O(1)** — es parte del
contrato, sin importar si por dentro se implementa con arreglo/vector o
con lista enlazada (semana 3 ya cubrió ambas bases).

## Qué hay en esta carpeta

Todavía nada — carpeta recién creada, ningún `.cpp` puesto aún.

## Reglas de la IA para esta carpeta

1. **Preguntar antes de crear archivos.** No asumir si Rola quiere un
   archivo por TDA (`pila.cpp`, `cola.cpp`, `deque.cpp`) o uno solo
   (`pilas_colas_deque.cpp`) con las tres, ni si prefiere clase con
   arreglo dinámico o con lista enlazada por debajo.
2. **No usar `std::stack`, `std::queue` ni `std::deque`** de la STL en
   las entregas — la idea es implementarlos a mano (igual que las listas
   de semana 3). Sí valen temporalmente en tests.
3. **Siempre incluir destructor** si la implementación usa `new`.
4. **Complejidad en comentarios** (`// O(1)`, etc.) en cada método
   público — parte de la evaluación del curso.
5. **Compilar y correr** (`g++ -O2 -std=c++17 archivo.cpp -o archivo`)
   antes de dar por lista una implementación.
6. **No mezclar material de Víctor con el de Luciano** sin avisar (ver
   nota del vault `AED.md`, sección "Notas sobre el material por sección").

---

**Mantenido por:** Rola · CS2023 semana 4 · UTEC 2026-2
