# Algoritmos Básicos

## 📌 Introducción

Un algoritmo es un conjunto de instrucciones paso a paso para resolver un problema. En ciencias de la computación, estudiamos algoritmos para:

1. **Resolver problemas eficientemente**
2. **Entender la complejidad computacional**
3. **Optimizar recursos (tiempo y memoria)**

## 🎯 Características de un Buen Algoritmo

- **Corrección:** Produce el resultado esperado
- **Eficiencia:** Usa recursos de forma óptima
- **Claridad:** Fácil de entender e implementar
- **Robustez:** Maneja casos especiales y errores

## 📊 Análisis de Complejidad

### Notación Big O

Mide cómo crece el tiempo de ejecución respecto al tamaño de la entrada.

| Notación | Nombre | Ejemplo |
|----------|--------|---------|
| O(1) | Constante | Acceso a elemento de array |
| O(log n) | Logarítmica | Búsqueda binaria |
| O(n) | Lineal | Búsqueda lineal |
| O(n log n) | Lineal-logarítmica | Merge Sort |
| O(n²) | Cuadrática | Burbuja, Inserción |
| O(2^n) | Exponencial | Fibonacci recursivo |
| O(n!) | Factorial | Permutaciones |

## 🔄 Algoritmos de Ordenamiento

### 1. Burbuja (Bubble Sort)

**Concepto:** Compara elementos adyacentes e intercambia si están desordenados.

**Ventajas:**
- Muy simple de entender e implementar
- Ordenamiento in-place (O(1) espacio)
- Estable (mantiene orden de elementos iguales)

**Desventajas:**
- Lento para arreglos grandes (O(n²))
- Muchos intercambios innecesarios

**Complejidad:**
- Mejor: O(n)
- Promedio: O(n²)
- Peor: O(n²)

**Ejemplo:**
```
Arreglo: [5, 2, 8, 1, 9]

Pasada 1: 
- Compara 5 y 2 → intercambia → [2, 5, 8, 1, 9]
- Compara 5 y 8 → no intercambia → [2, 5, 8, 1, 9]
- Compara 8 y 1 → intercambia → [2, 5, 1, 8, 9]
- Compara 8 y 9 → no intercambia → [2, 5, 1, 8, 9]

Pasada 2:
- Compara 2 y 5 → no intercambia
- Compara 5 y 1 → intercambia → [2, 1, 5, 8, 9]
- Compara 5 y 8 → no intercambia
...
```

### 2. Inserción (Insertion Sort)

**Concepto:** Construye el arreglo ordenado elemento por elemento.

**Ventajas:**
- Eficiente para arreglos pequeños
- Ordenamiento in-place
- Estable
- Eficiente para arreglos casi ordenados

**Complejidad:**
- Mejor: O(n)
- Promedio: O(n²)
- Peor: O(n²)

### 3. Quick Sort

**Concepto:** Divide y conquista usando un pivote.

**Ventajas:**
- Rápido en promedio O(n log n)
- In-place
- Muy usado en práctica

**Complejidad:**
- Mejor: O(n log n)
- Promedio: O(n log n)
- Peor: O(n²)

### 4. Merge Sort

**Concepto:** Divide el arreglo y luego combina ordenando.

**Ventajas:**
- Garantizado O(n log n)
- Estable
- Predecible

**Desventajas:**
- Requiere O(n) espacio adicional

**Complejidad:**
- Mejor: O(n log n)
- Promedio: O(n log n)
- Peor: O(n log n)

## 🔍 Algoritmos de Búsqueda

### 1. Búsqueda Lineal

Recorre el arreglo secuencialmente.

```
Complejidad: O(n)
Uso: Arreglos pequeños o desordenados
```

### 2. Búsqueda Binaria

Divide el espacio de búsqueda a la mitad repetidamente.

```
Complejidad: O(log n)
Requisito: Arreglo debe estar ordenado
```

## 💡 Consejos de Implementación

1. **Entiende el problema** antes de codificar
2. **Diseña el algoritmo** con pseudocódigo
3. **Implementa** paso a paso
4. **Prueba** con casos especiales (vacío, un elemento, máximo, etc.)
5. **Optimiza** solo después de que funcione

---

**Próximo tema:** Estructuras de Datos
