# Proyectos - Ciencias de la Computación

## 📋 Descripción

Esta sección contiene proyectos integradores que aplican múltiples conceptos aprendidos en clase.

## 🚀 Proyectos Implementados

### Proyecto 1: Comparador de Algoritmos de Ordenamiento ✅
**Nivel:** Principiante-Intermedio
**Conceptos:** Algoritmos, análisis de complejidad, conteo de operaciones
**Descripción:** Programa interactivo que compara 4 algoritmos de ordenamiento midiendo su eficiencia

**Archivo:** `01_comparador_algoritmos.cpp`

**Algoritmos Incluidos:**
- Burbuja (Bubble Sort) - O(n²)
- Quick Sort - O(n log n)
- Merge Sort - O(n log n)
- Heap Sort - O(n log n)

**Funcionalidades:**
- Ingresar números manualmente o generar aleatorios
- Ejecutar algoritmo individual
- Comparar todos los algoritmos simultáneamente
- Ver tabla comparativa con número de pasos
- Análisis de eficiencia relativa
- Validación de corrección de ordenamiento

**Cómo Compilar:**
```bash
cd /workspaces/Ciencias1_notas/proyectos
g++ -o comparador 01_comparador_algoritmos.cpp
```

**Cómo Ejecutar:**
```bash
./comparador
```

**Ejemplo de Salida:**
```
COMPARACION DE ALGORITMOS
Elementos: 50

Algoritmo      Pasos    Complejidad    Validación
Burbuja        1225     O(n²)          ✓ Correcto
Quick Sort     244      O(n log n)     ✓ Correcto
Merge Sort     286      O(n log n)     ✓ Correcto
Heap Sort      409      O(n log n)     ✓ Correcto

Análisis:
- Quick Sort es 5.02x más eficiente que Burbuja
- Los algoritmos O(n log n) mejoran significativamente con n grande
```

---

### Proyecto 2: Sudoku 4x4 y Suma Subsecuente Máxima ✅
**Nivel:** Intermedio
**Conceptos:** Fuerza bruta, backtracking, divide y vencerás, recursión
**Descripción:** Proyecto dual que resuelve un Sudoku 4x4 mediante fuerza bruta y calcula la suma subsecuente máxima usando divide y vencerás.

**Archivo:** `02_sudoku_y_suma.cpp`

**Parte A - Sudoku 4x4 (Fuerza Bruta):**
- Permite ingresar valores manualmente o generar un Sudoku aleatorio
- Representación del tablero 4x4 con subcuadros 2x2
- Validación de restricciones por fila, columna y subcuadro
- Resolución con backtracking (intenta valores 1..4 y retrocede)
- Métricas de análisis: intentos y retrocesos

**Complejidad (Sudoku):**
- Caso general aproximado: `O(4^k)` donde `k` es el número de casillas vacías
- Espacio: `O(k)` por la profundidad de recursión

**Parte B - Suma Subsecuente Máxima (Divide y Vencerás):**
- Divide el arreglo en dos mitades
- Resuelve recursivamente izquierda y derecha
- Calcula la mejor subsecuencia cruzando el punto medio
- Elige el máximo entre izquierda, derecha y cruzada

**Complejidad (Suma Subsecuente):**
- Tiempo: `O(n log n)`
- Espacio: `O(log n)` por recursión

**Cómo Compilar:**
```bash
cd /workspaces/Ciencias1_notas/proyectos
g++ -o proyecto2 02_sudoku_y_suma.cpp
```

**Cómo Ejecutar:**
```bash
./proyecto2
```

**Análisis Comparativo de Técnicas:**
- La fuerza bruta explora el espacio de soluciones y garantiza encontrar una respuesta si existe.
- Divide y vencerás reduce el problema en subproblemas y mejora la eficiencia sobre enfoques cuadráticos.
- Ambas técnicas usan recursión, pero con objetivos distintos: búsqueda exhaustiva vs optimización estructurada.

---

### Proyecto 3: Tablero NxN con Piezas de Ajedrez ✅
**Nivel:** Intermedio
**Conceptos:** Backtracking, poda, validación de restricciones
**Descripción:** Programa interactivo que ubica una cantidad configurable de piezas iguales en un tablero de tamaño configurable (NxN) sin que se amenacen entre sí.

**Archivo:** `03_tablero_5x5_piezas.cpp`

**Piezas soportadas (a elección del usuario):**
- Peones
- Caballos
- Alfiles
- Torres
- Reinas

**Funcionalidades:**
- Menú para elegir tipo de pieza
- Entrada del tamaño del tablero (NxN)
- Entrada de la cantidad de fichas objetivo
- Búsqueda de posiciones válidas con backtracking
- Explicación paso a paso del proceso de búsqueda (búsqueda, descarte, encrucijada, vuelta atrás)
- Mostrar posiciones encontradas
- Renderizado del tablero NxN en consola

**Cómo Compilar:**
```bash
cd /workspaces/Ciencias1_notas/proyectos
g++ -o tablero_ajedrez_5x5 03_tablero_5x5_piezas.cpp
```

**Cómo Ejecutar:**
```bash
./tablero_ajedrez_5x5
```

---

### Proyecto 4: Voraz y Vuelta Atrás (Monedas + Sudoku 9x9) ✅
**Nivel:** Intermedio
**Conceptos:** Greedy, backtracking, poda, validación robusta, manejo de errores
**Descripción:** Menú completo con dos ejercicios: cambio de monedas con técnica voraz y resolución de Sudoku 9x9 con backtracking.

**Archivo:** `04_greedy_backtracking.cpp`

**Parte A - Cambio de Monedas (Greedy):**
- Usa denominaciones fijas en pesos colombianos: 50, 100, 200, 500, 1000
- Permite ingresar la cantidad objetivo manualmente o generarla aleatoriamente
- Ordena monedas de mayor a menor para aplicar la estrategia voraz
- Muestra el proceso paso a paso (qué moneda toma y restante)
- Determina si el cambio exacto es posible o no
- Incluye validaciones de rango con `try/catch`

**Parte B - Sudoku 9x9 (Backtracking):**
- Permite cargar tablero de ejemplo, ingreso manual o generación aleatoria
- Usa `0` para casillas vacías
- Valida conflictos iniciales por fila, columna y subcuadro
- Resuelve con vuelta atrás y poda de posibilidades inválidas
- Muestra métricas: intentos, asignaciones, retrocesos y podas
- Opción para mostrar pasos de resolución explicados

**Cómo Compilar:**
```bash
cd /workspaces/Ciencias1_notas/proyectos
g++ -std=c++11 -O2 -Wall -o proyecto4 04_greedy_backtracking.cpp
```

**Cómo Ejecutar:**
```bash
./proyecto4
```

---

## 🎯 Proyectos Futuros Propuestos

### Proyecto 5: Sistema de Gestión de Estudiantes
**Nivel:** Intermedio
**Conceptos:** Estructuras, archivos, búsqueda
**Descripción:** Gestionar información de estudiantes (nombre, edad, calificaciones)

### Proyecto 6: Visualizador Gráfico de Algoritmos
**Nivel:** Avanzado
**Conceptos:** Gráficos, animaciones, interfaz
**Descripción:** Visualizar paso a paso cómo trabajan los algoritmos

### Proyecto 7: Compilador Simple
**Nivel:** Avanzado
**Conceptos:** Parsing, análisis léxico, árboles
**Descripción:** Compilador básico para un lenguaje sencillo

---

## 📈 Recomendaciones

1. Comienza con proyectos pequeños
2. Lee código de otros programadores
3. Refactoriza después de que funcione
4. Escribe pruebas
5. Documenta tu código

---

**Última actualización:** Marzo 2026
