# AI Context — semana 7

> Contexto específico para los archivos de esta carpeta. Se complementa
> con `../AI_CONTEXT.md` (raíz) y con la nota del vault
> `Utec 6to/AED/AED.md` — **leelos primero**.

## Tema de la semana

**Heaps (montículos) y colas de prioridad**. Material del **profe Víctor
Racsó Galván Oyola** (`vgalvan@utec.edu.pe`), no de Luciano. Mismo
tratamiento que semanas 3 a 6: material de apoyo de otra sección.

**PDFs de la clase (leer si hace falta más detalle o ejemplos):**
- `/home/rola/Documents/Obsidian Vault/Utec 6to/AED/Semana 7/Sem7_Heaps.pdf` — *Heaps* (teoría, 21 sep)
- `/home/rola/Documents/Obsidian Vault/Utec 6to/AED/Semana 7/Sem7_Implementacion_Heap.pdf` — *Implementación de Heaps* (22 sep)

Resumen ya hecho en el vault: `Utec 6to/AED/Semana 7/Resumen.md`, con todo
el pseudocódigo y ejemplos paso a paso de Insertar y Extraer.

## Qué toca implementar

Un **min-heap sobre arreglo**, a mano (sin `std::priority_queue`,
`std::make_heap` ni `std::push_heap` en la entrega).

### Estructura
- `vector<T> H` **1-indexado** (la convención de la clase: dejar `H[0]` sin
  usar o insertar un valor de relleno).
- Campo `n` = tamaño actual del heap.
- Índices: `padre(i) = i / 2`, `izq(i) = 2 * i`, `der(i) = 2 * i + 1`.
- Propiedad min-heap: `H[padre(i)] <= H[i]` para todo `i > 1`.

### Operaciones (seguir el pseudocódigo del resumen)
| Operación | Detalle | Complejidad |
|---|---|---|
| `siftUp(i)` | Mientras `i > 1` y `H[padre(i)] > H[i]`: intercambiar y subir | O(lg n) |
| `siftDown(i, n)` | Intercambiar con el **menor** de los hijos mientras sea mayor que alguno | O(lg n) |
| `verExtremo()` / `top()` | Devuelve `H[1]` | O(1) |
| `insertar(x)` | Poner en `H[n + 1]`, `n++`, `siftUp(n)` | O(lg n) |
| `extraerExtremo()` / `pop()` | Guardar `H[1]`, mover `H[n]` a `H[1]`, `n--`, `siftDown(1, n)` | O(lg n) |
| `construirHeap(arreglo)` | Copiar y hacer `siftDown(i, n)` para `i = n/2` hasta `1` | **O(n)** |
| `heapsort(arreglo)` | Construir-Heap + n veces: intercambiar `H[1]` con el último activo, reducir y `siftDown(1)` | O(n lg n) in-place |

Para heapsort en orden creciente conviene un **max-heap** (o usar el min-heap
y leer al revés): comentar la decisión en el código.

### Casos de prueba sugeridos
- El ejemplo de clase: `H = [2, 4, 3, 8, 6, 9, 7]` es un min-heap válido.
- Insertar 1 en ese heap → `[1, 2, 3, 4, 6, 9, 7, 8]` (3 intercambios).
- Extraer del heap original → devuelve 2 y queda `[3, 4, 7, 8, 6, 9]`.
- `construirHeap` sobre un arreglo desordenado y verificar la propiedad
  recorriendo todos los `i > 1`.
- Heapsort contra `std::sort` con arreglos aleatorios (solo en el test).
- Extraer de un heap vacío: decidir qué pasa (excepción o valor centinela).

## Qué hay en esta carpeta

Todavía nada: solo este archivo.

## Reglas de la IA para esta carpeta

1. **Preguntar antes de crear archivos.** No asumir el nombre (p.ej.
   `heap.cpp`, `minheap.cpp`) ni si Rola quiere `template<typename T>` o
   algo fijado a `int`.
2. **No usar `std::priority_queue` ni las funciones `*_heap` de la STL** en
   la entrega; sí valen en tests para comparar resultados.
3. **Respetar la convención 1-indexada** de la clase (si se usa 0-indexado,
   avisar y cambiar las fórmulas a `2i+1`, `2i+2`, `(i-1)/2`).
4. **Sift-Down con el menor hijo**, no con cualquiera: es el error típico que
   el profe remarca.
5. **Complejidad en comentarios** en cada método público: es parte de la
   evaluación del curso.
6. **Compilar y correr** (`g++ -O2 -std=c++17 archivo.cpp -o archivo`) antes
   de dar por lista una implementación.
7. **No mezclar material de Víctor con el de Luciano** sin avisar (ver nota
   del vault `AED.md`, sección "Notas sobre el material por sección").

---

**Mantenido por:** Rola · CS2023 semana 7 · UTEC 2026-2
