# AI Context — semana 6

> Contexto específico para los archivos de esta carpeta. Se complementa
> con `../AI_CONTEXT.md` (raíz) y con la nota del vault
> `Utec 6to/AED/AED.md` — **leelos primero**.

## Tema de la semana

**Árboles y Árbol Binario de Búsqueda (BST)**. Material del **profe Víctor
Racsó Galván Oyola** (`vgalvan@utec.edu.pe`), no de Luciano. Mismo
tratamiento que semanas 3, 4 y 5: material de apoyo de otra sección.

**PDFs de la clase (leer si hace falta más detalle o ejemplos):**
- `/home/rola/Documents/Obsidian Vault/Utec 6to/AED/Semana 6/Sem6_BST.pdf` — *Árbol binario de búsqueda* (teoría, 14 sep)
- `/home/rola/Documents/Obsidian Vault/Utec 6to/AED/Semana 6/CS2023_Algoritmos_y_Estructuras_de_Datos_2s2026 (4).pdf` — *Implementación de BST* (15 sep)

Resumen ya hecho en el vault: `Utec 6to/AED/Semana 6/Resumen.md`. La
**sección 8** tiene el pseudocódigo de las 7 operaciones. Ojo: en el PDF las
láminas de Insertar y Eliminar vienen en blanco; el resumen las reconstruye
con CLRS.

## Qué toca implementar

El TDA **BST** a mano, con nodos y punteros (sin `std::set` ni `std::map` en
la entrega).

### Estructura
- Nodo con `clave`, `izq`, `der` y **`padre`** (el profe insiste en `padre`:
  es lo que permite Sucesor y Eliminar sin volver a bajar desde la raíz).
- Clase árbol con puntero `raiz` (nulo si está vacío).
- Propiedad BST como en la clase: subárbol izquierdo `≤` nodo `≤` subárbol
  derecho (el profe la enuncia con desigualdades no estrictas).

### Operaciones (seguir el pseudocódigo del resumen)
| Operación | Detalle | Complejidad |
|---|---|---|
| `buscar(k)` | Recursivo o iterativo; compara y baja por el lado correcto | O(h) |
| `minimo(x)` / `maximo(x)` | Siempre a la izquierda / derecha | O(h) |
| `insertar(k)` | Baja como en buscar recordando el último nodo `y`; cuelga el nuevo como hijo de `y` y asigna `padre` | O(h) |
| `sucesor(x)` / `predecesor(x)` | Caso 1: mínimo (máximo) del subárbol derecho (izquierdo). Caso 2: subir por `padre` | O(h) |
| `transplantar(u, v)` | Helper: reemplaza el subárbol de `u` por el de `v`, solo reconecta punteros | O(1) |
| `eliminar(z)` | 3 casos: 0 hijos, 1 hijo, 2 hijos (con el sucesor; distinguir si `y.padre == z`) | O(h) |
| `inorder(x)` | Izquierda, visitar, derecha; debe imprimir en orden creciente | Θ(n) |

Extras útiles para probar: `preorder`, `postorder`, `altura()`.

### Casos de prueba sugeridos
- El ejemplo de la clase: insertar 8, 3, 10, 1, 6 y luego 7 → el 7 queda como
  hijo derecho de 6; `inorder` = 1 3 6 7 8 10.
- Eliminar una hoja, un nodo con un hijo, un nodo con dos hijos cuyo sucesor
  es hijo directo y otro cuyo sucesor está más abajo.
- Eliminar la raíz.
- Insertar datos **ya ordenados** (1, 2, 3, …, n) y medir la altura: debe
  salir `n − 1` (árbol degenerado, el talón de Aquiles del BST).

## Qué hay en esta carpeta

Todavía nada: solo este archivo.

## Reglas de la IA para esta carpeta

1. **Preguntar antes de crear archivos.** No asumir el nombre (p.ej.
   `bst.cpp`) ni si Rola quiere `template<typename T>` o algo fijado a `int`.
2. **No usar `std::set`, `std::map` ni `std::multiset`** en la entrega; sí
   valen temporalmente en tests para comparar resultados.
3. **Siempre incluir destructor** que libere todos los nodos (recorrido
   postorder).
4. **Mantener `padre` consistente** en insertar, transplantar y eliminar;
   es el error más común.
5. **Complejidad en comentarios** (`// O(h)`, `// Θ(n)`) en cada método
   público: es parte de la evaluación del curso.
6. **Compilar y correr** (`g++ -O2 -std=c++17 archivo.cpp -o archivo`) antes
   de dar por lista una implementación.
7. **No mezclar material de Víctor con el de Luciano** sin avisar (ver nota
   del vault `AED.md`, sección "Notas sobre el material por sección").

---

**Mantenido por:** Rola · CS2023 semana 6 · UTEC 2026-2
