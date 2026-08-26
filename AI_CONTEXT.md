# AI Context — newutec

> Este archivo es leído por la IA cada vez que se abra el proyecto
> (Zed, terminal, agente de código, etc.). Mantenerlo corto y autoritativo.

## ¿Qué es este proyecto?

Es el **workspace de código** del curso **Algoritmos y Estructuras de
Datos (CS2023)** de UTEC, 6to ciclo, 2026-2. La documentación, apuntes y
resúmenes viven en otro lado (Obsidian); **aquí solo va código C++**.

## Relación con el vault de Obsidian

- **Vault:** `~/Documents/Obsidian Vault/`
- **Nota de contexto del curso:** `Utec 6to/AED/AED.md`
  (`/home/rola/Documents/Obsidian Vault/Utec 6to/AED/AED.md`)

Esa nota describe sílabo, evaluación, metodología, profe (Luciano A. Romero
Calla, `lromeroc@utec.edu.pe`) y el resto del material. **Léela primero**
si necesitás entender de qué va el curso, qué toca esta semana o cómo se
evalúa. No la dupliques: mantenete consistente con lo que dice.

## Estructura

```
newutec/
├── AI_CONTEXT.md          ← este archivo
├── semana 1/              ← ejercicios y envíos de la semana 1
│   ├── AI_CONTEXT.md      ← contexto específico de la semana
│   ├── problem1.cpp ...   ← soluciones / intentos
│   └── enviar*            ← binarios ya compilados para envío
├── semana 2/              ← (cuando exista)
└── ...
```

- **Una carpeta por semana** (`semana N/`).
- Dentro, los `.cpp` con el nombre del problema (`problemN.cpp`) y, si ya
  fueron compilados para entregar, los binarios `enviarN` (+ `.cpp`).
- Si una semana no tiene carpeta, todavía no se trabajó en ella — no la
  crees de antemano.

## Reglas de trabajo para la IA

1. **Lee la nota `Utec 6to/AED/AED.md` antes de inventar nada.** Ahí está
   el temario, las PCs, la metodología y los pendientes del curso.
2. **Trabaja sobre los archivos que ya existen** (`problemN.cpp`,
   `enviarN.cpp`) en vez de crear archivos nuevos con otro nombre, salvo
   que el usuario lo pida explícitamente.
3. **No mezcles secciones.** El vault puede tener material de otra
   sección del mismo curso (profe Víctor Racsó Galván Oyola). Si ves
   criterios distintos (60/40 vs 50/50, PCs en sem 2/4/6/10/12/14), no
   los apliques a este proyecto a menos que el usuario confirme que
   trabaja con esa sección.
4. **Compila y prueba antes de entregar.** Los envíos van en
   `enviar*.cpp` + binario `enviar*`. No entregues un binario sin haberlo
   corrido al menos con los casos de la lista de ejercicios.
5. **No borres archivos** a menos que el usuario lo pida. Los `probem*`
   viejos son intentos anteriores, a veces sirven para ver el
   razonamiento.
6. **Lenguaje del curso:** C++. Salvo que el usuario diga lo contrario,
   no uses C, Python u otro.

## Cómo pedirle cosas a la IA

Decile en español (o el idioma que estés usando), y mencioná la semana y
el problema si aplica. Ejemplos:

- *"Revisame el `enviar2.cpp` de semana 1, creo que tiene TLE en el caso
  grande."*
- *"Implementame una lista doblemente enlazada para la semana 3."*
- *"¿Qué complejidad tiene mi solución de `problem4.cpp`?"*

Si la IA te responde algo inconsistente con el sílabo o la evaluación,
peganearle el link a `Utec 6to/AED/AED.md` y pedirle que reconcilie.

---

**Mantenido por:** Rola · Curso CS2023 (AED) · UTEC 6to ciclo 2026-2
