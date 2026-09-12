# AI Context — semana 5

> Contexto específico para los archivos de esta carpeta. Se complementa
> con `../AI_CONTEXT.md` (raíz) y con la nota del vault
> `Utec 6to/AED/AED.md` — **leelos primero**.

## Tema de la semana

**Diccionarios y Tablas Hash** — Diccionarios y Hashing (semana 5 del
sílabo). Material del **profe Víctor Racsó Galván Oyola**
(`vgalvan@utec.edu.pe`), no de Luciano. Mismo tratamiento que semanas 3 y 4:
material de apoyo de otra sección mientras llega el oficial.

**PDFs de la clase (leer si hace falta más detalle o ejemplos):**
- `/home/rola/Documents/Obsidian Vault/Utec 6to/AED/Semana 5/CS2023_Algoritmos_y_Estructuras_de_Datos_2s2026 (2).pdf` — *Diccionarios* (teoría)
- `/home/rola/Documents/Obsidian Vault/Utec 6to/AED/Semana 5/CS2023_Algoritmos_y_Estructuras_de_Datos_2s2026 (3).pdf` — *Implementación de diccionarios*

(resumen ya hecho en el vault: `Utec 6to/AED/Semana 5/Resumen.md`, con
todo el pseudocódigo y la teoría en detalle).

## Qué toca implementar

El TDA **Diccionario** (map: `insertar(clave, valor)` / `buscar(clave)` /
`eliminar(clave)`), implementado **a mano** como una **tabla hash con
encadenamiento separado** (chaining) — sin usar `std::unordered_map` ni
`std::map` de la STL en la entrega.

### Estructura
- Un `vector` de punteros a nodo (`buckets`), tamaño `m`.
- Cada nodo: `clave`, `valor`, puntero `siguiente` (lista simple, igual que
  semana 3, con un campo extra para el valor).
- Campo `n`: cantidad total de claves guardadas.

### Función hash
- Claves enteras: método de la división, `h(k) = k mod m`, con `m` **primo**
  (evitar potencias de 2).
- Claves `string`: hashing polinomial (`val(s) = Σ s_i·B^i mod M`, con
  `B > tamaño del alfabeto`, p.ej. 131 o 257) y luego `mod m`.

### Operaciones (todas O(1) esperado / amortizado)
| Operación | Efecto |
|---|---|
| `insertar(clave, valor)` | agrega el par o actualiza si la clave ya existía |
| `buscar(clave)` | devuelve el valor asociado o "no encontrado" |
| `eliminar(clave)` | quita el par con esa clave |

### Rehash / crecimiento
- Factor de carga `α = n / m`.
- Cuando `(n+1)/m ≥ 0.75` (justo antes de insertar el nodo nuevo): duplicar
  `m`, recorrer todos los buckets viejos y reinsertar cada nodo en la tabla
  nueva (reutilizando el nodo, sin `new`/`delete` extra) — igual patrón que
  el crecimiento amortizado de `vector`.

### Aplicación de prueba
- Conteo de frecuencias de palabras en un texto (ver pseudocódigo
  `CONTAR-PALABRAS` en el `Resumen.md` del vault) — buen caso de prueba end
  to end para `insertar`/`buscar`.

## Qué hay en esta carpeta

Todavía nada — carpeta recién creada, ningún `.cpp` puesto aún.

## Reglas de la IA para esta carpeta

1. **Preguntar antes de crear archivos.** No asumir el nombre (p.ej.
   `hashtable.cpp` vs `diccionario.cpp`) ni si Rola quiere una clase
   template (`template<typename K, typename V>`) o algo fijado a
   `string`/`int`.
2. **No usar `std::unordered_map`, `std::map` ni `std::hash`** de la STL en
   la entrega — la idea es implementar la función hash y la tabla a mano.
   Sí valen temporalmente en tests para comparar resultados.
3. **`m` inicial primo** (p.ej. 7 o 11) y **duplicar+buscar el siguiente
   primo** (o al menos duplicar) al hacer rehash — no dejar `m` como
   potencia de 2 sin más.
4. **Siempre incluir destructor** que libere todos los nodos de todos los
   buckets (recorrer cada lista, como en semana 3).
5. **Complejidad en comentarios** (`// O(1) esperado`, `// O(m) amortizado
   O(1)`, etc.) en cada método público — parte de la evaluación del curso.
6. **Compilar y correr** (`g++ -O2 -std=c++17 archivo.cpp -o archivo`) antes
   de dar por lista una implementación.
7. **No mezclar material de Víctor con el de Luciano** sin avisar (ver nota
   del vault `AED.md`, sección "Notas sobre el material por sección").

---

**Mantenido por:** Rola · CS2023 semana 5 · UTEC 2026-2
