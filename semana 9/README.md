# Semana 9 — AVL Tree (implementación "normal", sin Red-Black)

Contexto de la Semana 9 de AED (CS2023). La teoría completa (AVL y Red-Black)
está resumida en el vault: `Utec 6to/AED/Semana 9/Resumen_Semana9.pdf`.
Acá solo implementamos el **AVL estándar** — el Red-Black queda solo como
teoría, no se pide implementarlo.

## Objetivo

Implementar un árbol AVL (BST autobalanceado por altura) recursivo, en C++,
con las operaciones básicas y verificación de que el árbol sigue siendo AVL
después de cada operación.

## Qué implementar

### 1. El nodo
Campos: `clave`, `izq`, `der`, `altura` (altura de su propio subárbol).
**No** se guarda puntero al padre — todo se hace recursivo: cada función
recibe la raíz de un subárbol y devuelve la nueva raíz de ese subárbol.

### 2. Funciones auxiliares — O(1) cada una
- `h(v)`: con `h(nulo) = -1`, devuelve `v->altura`.
- `actualizar(v)`: `v->altura = 1 + max(h(v->izq), h(v->der))`.
- `fb(v)` (factor de balance): `h(v->izq) - h(v->der)`.

Regla: llamar `actualizar(v)` **cada vez que cambia un hijo de `v`**.

### 3. Rotaciones — O(1), reconectan 3 punteros
- `rotarDerecha(y)`: `x = y->izq`; `y->izq = x->der`; `x->der = y`;
  actualizar `y` primero, luego `x`; devolver `x`.
- `rotarIzquierda(x)`: el espejo exacto.

**Ojo:** el orden de los `actualizar` importa — el nodo que queda abajo
(`y` en rotarDerecha) se actualiza antes que el que queda arriba (`x`),
porque la altura de `x` depende de la de `y` ya corregida.

### 4. Rebalancear(v) — se llama al volver de cada inserción/eliminación
```
actualizar(v)
si fb(v) > 1:
    si fb(v->izq) < 0: v->izq = rotarIzquierda(v->izq)   // caso LR
    devolver rotarDerecha(v)                              // caso LL
si fb(v) < -1:
    si fb(v->der) > 0: v->der = rotarDerecha(v->der)      // caso RL
    devolver rotarIzquierda(v)                             // caso RR
devolver v   // ya estaba balanceado
```

### 5. Insertar(v, k)
Es el insertar del BST normal, recursivo, con una línea nueva al final:
```
si v == nulo: devolver nuevo nodo (clave=k, altura=0)
si k < v->clave: v->izq = Insertar(v->izq, k)
si no:           v->der = Insertar(v->der, k)
devolver Rebalancear(v)
```
Al volver de la recursión se pasa por todos los ancestros del nodo nuevo:
son los únicos cuya altura pudo cambiar. Insertar rota **a lo más una vez**
(simple o doble) en total.

### 6. Eliminar(v, k)
Los 3 casos del BST (sin hijo izq., sin hijo der., dos hijos → copiar clave
del sucesor y eliminarlo del subárbol derecho), con `Rebalancear(v)` al
volver. Diferencia con Insertar: eliminar puede rotar **en varios niveles**
(hasta O(lg n) veces), porque una rotación puede dejar el subárbol más bajo
de lo que estaba y desbalancear a un ancestro más arriba.

### 7. Buscar(v, k) / Mínimo(v) / Máximo(v)
Iguales a un BST normal — no tocan el balance, solo leen.

### 8. Verificar(v, lo, hi) — para probar la implementación
Recorre el árbol y devuelve `h(v)` o "falla" si:
- no se cumple el orden BST (`lo < v->clave < hi`), o
- `v->altura` guardada no coincide con `1 + max(alturaIzq, alturaDer)`, o
- `|fb(v)| > 1`.

Se llama como `Verificar(raiz, -infinito, +infinito)`. Cuesta O(n): es para
probar después de cada operación en las pruebas, no para usar en producción.

## Casos de prueba sugeridos (de la teoría, para comparar a mano)

- Insertar `10, 20, 30` → debe rotar una vez (caso LL en 30... revisa el
  signo con tu propio código) y quedar `20[10, 30]`.
- Insertar `30, 10, 20` → caso LR (dos rotaciones), mismo resultado final
  `20[10, 30]`.
- Insertar `10, 20, 30, 40, 50, 25` → al insertar el 25 se desbalancea el
  nodo 20 (caso RL): dos rotaciones, dos niveles.
- Insertar `1, 2, 3, 4, 5, 6, 7` en orden → el AVL debe rotar 4 veces
  (siempre caso RR) y terminar **perfecto**: `4[2[1,3], 6[5,7]]`, altura 2.
  (Un BST sin balancear terminaría como una cadena de altura 6.)
- Eliminar de un AVL de 12 claves (5[3[2[1],4], 8[7[6],10[9,11[,12]]]])
  la hoja `4` → debe rotar en dos niveles distintos (primero arregla el
  nodo 3, pero eso baja su altura y desbalancea a 5 más arriba).

## Errores comunes a evitar (de la teoría)

- Llamar a `Insertar`/`Eliminar`/una rotación **sin colgar lo que
  devuelven**: tiene que ser `v->izq = Insertar(v->izq, k)`, no solo
  `Insertar(v->izq, k)`.
- Actualizar `x` antes que `y` en `rotarDerecha` (la altura de `x` depende
  de la de `y` ya corregida).
- Calcular `fb(v)` en `Rebalancear` **antes** de llamar `actualizar(v)`.
- Recalcular la altura recorriendo todo el subárbol en vez de leerla de los
  hijos — eso vuelve cada operación O(n) en vez de O(1).
- Mezclar convenciones de altura: con `h(nulo) = -1`, una hoja tiene
  altura 0, no 1.

## Complejidad esperada

| Operación              | Tiempo   | Rotaciones        |
|-------------------------|----------|--------------------|
| Buscar, Mínimo, Máximo | O(lg n)  | —                  |
| Insertar                | O(lg n)  | a lo más 2         |
| Eliminar                | O(lg n)  | O(lg n)            |

Espacio: O(n), con un entero extra por nodo (`altura`).

## Estructura sugerida de archivos

```
semana 9/
├── avl.h       // struct Nodo + declaración de la clase/funciones del AVL
├── avl.cpp     // implementación: Insertar, Eliminar, Buscar, Rotaciones...
├── main.cpp    // pruebas con los casos sugeridos arriba
└── README.md   // este archivo
```

## Referencia

Teoría completa (AVL + Red-Black, con dibujos y ejemplos paso a paso) en el
vault: `Utec 6to/AED/Semana 9/Resumen_Semana9.pdf` — secciones 3 y 4 son las
que aplican acá (Red-Black, secciones 5-6, es solo para el examen, no para
este código).
