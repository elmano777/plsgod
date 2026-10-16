# Semana 10 — Recursión y Backtracking

Contexto de la Semana 10 de AED (CS2023). Teoría completa (recursión,
pila de llamadas, árbol de recursión, subconjuntos/permutaciones/
combinaciones, backtracking con poda, Torres de Hanói, notación prefija)
en el vault: `Utec 6to/AED/Semana 10/Resumen_Semana10.pdf`, y el repaso
combinado para la PC (Semana 9 + 10 + consejos de código) en
`Utec 6to/AED/Semana 10/Repaso_PC_Semana9_10.pdf`.

## Qué hay acá

- **`reinas.cpp`** — N-reinas, el ejemplo completo de recursión +
  backtracking. Implementa las dos variantes del resumen:
  - `buscar(f)` — guarda todas las soluciones (equivale a `Reinas(f)` del
    pseudocódigo, que "imprime").
  - `contar(f)` — solo cuenta cuántas hay, sin guardar nada (equivale a
    `Contar(f)`).

  Usa tres `vector<bool>` (`col`, `d1`, `d2`) para marcar columnas,
  diagonales y antidiagonales ocupadas — cada verificación es O(1), igual
  que en la teoría. El patrón hacer–explorar–deshacer está en `marcar(...,
  true)` → `buscar(f+1)` → `marcar(..., false)`.

  Las pruebas en `main()` comparan contra la secuencia conocida de
  soluciones de N-reinas (OEIS A000170: 1, 0, 0, 2, 10, 4, 40, 92 para
  n=1..8) y contra los números exactos que trae el resumen: la primera
  solución para n=4 es `(1,3,0,2)` en **17 llamadas**, y `Contar(f)` para
  n=8 hace **2057 llamadas** — los dos coinciden exacto con la teoría.

  Compilar y correr:
  ```
  g++ -std=c++17 -Wall -Wextra -O2 -o reinas reinas.cpp && ./reinas
  ```

## Qué falta (pendiente, para cuando Rola quiera practicar más)

El resumen trae varios problemas más que todavía no tienen código acá —
buenos candidatos para el mismo tratamiento que `reinas.cpp` (con `check()`
y casos conocidos):

- **Subconjuntos / Permutaciones / Combinaciones** — generación pura,
  sin poda (sección "Generar todas las opciones" del resumen).
- **Suma de subconjuntos con poda** — backtracking sobre un arreglo
  ordenado, corta cuando `s + a[i] > T`.
- **Torres de Hanói** — recursión con predicado fortalecido
  (`Hanoi(n, origen, destino, apoyo)`); fácil de verificar contando
  movimientos ($2^n-1$).
- **Notación prefija** — recursión que devuelve dos datos (valor y
  posición); en C++ con `pair<int,int>` o pasando la posición por
  referencia (`int&`).
- **Paréntesis balanceados** — backtracking con dos contadores
  (`ab`, `ce`); verificar contra los números de Catalan.
- **Sudoku 4×4 o 9×9** — el mismo esquema de `reinas.cpp` pero con tres
  tablas (`fila`, `columna`, `bloque`) en vez de tres (`col`, `d1`, `d2`).

## Relación con el resto del curso

Igual que semanas anteriores: BST (`semana 6/bst.cpp`), Heap
(`semana 7/heap.cpp`) y AVL (`semana 9/avl.cpp`) ya están implementados y
probados. Esta semana no trae árboles nuevos — es recursión/backtracking
puro; ver `Utec 6to/AED/AED.md` para el estado general del curso.
