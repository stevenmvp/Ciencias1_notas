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

## 🎯 Proyectos Futuros Propuestos

### Proyecto 3: Sistema de Gestión de Estudiantes
**Nivel:** Intermedio
**Conceptos:** Estructuras, archivos, búsqueda
**Descripción:** Gestionar información de estudiantes (nombre, edad, calificaciones)

### Proyecto 4: Visualizador Gráfico de Algoritmos
**Nivel:** Avanzado
**Conceptos:** Gráficos, animaciones, interfaz
**Descripción:** Visualizar paso a paso cómo trabajan los algoritmos

### Proyecto 5: Compilador Simple
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

**Última actualización:** Febrero 2026
