#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <set>

using namespace std;

// Variables globales para estadísticas
int comparaciones = 0;
int intercambios = 0;
int msDelay = 50; // Milisegundos de delay entre actualizaciones
bool permitirRepetidos = true;

struct ResAlgoritmo {
    string nombre;
    long long tiempo;
    int compars;
    int intercam;
};

void limpiarPantalla() {
    system("clear");
}

void mostrarEncabezado(const string& titulo) {
    cout << "\n╔";
    for (int i = 0; i < 60; i++) cout << "═";
    cout << "╗\n";
    cout << "║ " << setw(58) << left << titulo << "║\n";
    cout << "╠";
    for (int i = 0; i < 60; i++) cout << "═";
    cout << "╣\n";
}

vector<int> generarArreglo(int tamano, bool repetidos) {
    vector<int> arr;
    
    if (repetidos) {
        // Números aleatorios con rango más amplio para mayor variabilidad
        for (int i = 0; i < tamano; i++) {
            arr.push_back(rand() % 500 + 1);
        }
    } else {
        // Sin repetidos: usar set y luego mezclar
        set<int> sinDuplicados;
        while (sinDuplicados.size() < tamano) {
            // Rango más amplio para garantizar números distintos y variados
            sinDuplicados.insert(rand() % (tamano * 50));
        }
        for (int x : sinDuplicados) {
            arr.push_back(x);
        }
        // Mezclar el arreglo porque set lo mantiene ordenado
        for (int i = 0; i < tamano; i++) {
            int swapIdx = rand() % tamano;
            swap(arr[i], arr[swapIdx]);
        }
    }
    
    return arr;
}

void mostrarBarras(const vector<int>& arr, int maxVal, int indiceActual = -1, int indiceTrabajando = -1, const string& info = "") {
    cout << "\n";
    if (info != "") {
        cout << "  INFO: " << info << "\n";
    }
    for (int i = 0; i < arr.size(); i++) {
        // Mostrar índice
        cout << "[" << setw(2) << i << "] ";
        
        int altura = (arr[i] * 15) / maxVal;
        if (altura < 1) altura = 1;
        
        if (i == indiceActual) {
            cout << "\033[1;32m"; // Verde - comparando
        } else if (i == indiceTrabajando) {
            cout << "\033[1;31m"; // Rojo - trabajando
        } else {
            cout << "\033[1;37m"; // Blanco
        }
        
        for (int j = 0; j < altura; j++) {
            cout << "█";
        }
        cout << "\033[0m";
        
        // Mostrar valor
        cout << " " << setw(3) << arr[i];
        
        if (i == indiceActual) cout << " \033[1;32m★ comparando\033[0m";
        if (i == indiceTrabajando) cout << " \033[1;31m★ trabajando\033[0m";
        cout << "\n";
    }
    cout << flush;
}

void mostrarEstadisticas() {
    cout << "\n================================================\n";
    cout << "Comparaciones: " << comparaciones << "\n";
    cout << "Intercambios:  " << intercambios << "\n";
    cout << "================================================\n";
}

// ===== BURBUJA =====
void burbuja(vector<int> arr) {
    comparaciones = 0;
    intercambios = 0;
    int maxVal = *max_element(arr.begin(), arr.end());
    int n = arr.size();
    
    auto inicio = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparaciones++;
            limpiarPantalla();
            mostrarEncabezado("BURBUJA - Ordenando");
            cout << "║ Iteración externa: " << (i + 1) << "/" << (n - 1) 
                 << " | Comparación: " << comparaciones 
                 << " | Intercambios: " << intercambios << setw(10) << "║\n";
            cout << "╚";
            for (int k = 0; k < 60; k++) cout << "═";
            cout << "╝";
            mostrarBarras(arr, maxVal, j, j + 1);
            this_thread::sleep_for(chrono::milliseconds(msDelay));
            
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                intercambios++;
            }
        }
    }
    
    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
    
    limpiarPantalla();
    mostrarEncabezado("✓ BURBUJA COMPLETADO");
    cout << "║ Tiempo total: " << setw(46) << (to_string(duracion.count()) + " ms") << "║\n";
    cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
    cout << "║ Intercambios: " << setw(45) << intercambios << "║\n";
    cout << "╚";
    for (int i = 0; i < 60; i++) cout << "═";
    cout << "╝\n";
    mostrarBarras(arr, maxVal, -1, -1);
}

// ===== INSERCIÓN =====
void insercion(vector<int> arr) {
    comparaciones = 0;
    intercambios = 0;
    int maxVal = *max_element(arr.begin(), arr.end());
    int n = arr.size();
    
    auto inicio = chrono::high_resolution_clock::now();
    
    for (int i = 1; i < n; i++) {
        int clave = arr[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparaciones++;
            limpiarPantalla();
            mostrarEncabezado("INSERCIÓN - Ordenando");
            cout << "║ Elemento a insertar: " << (i + 1) << "/" << n 
                 << " | Comparación: " << comparaciones 
                 << " | Intercambios: " << intercambios << setw(8) << "║\n";
            cout << "╚";
            for (int k = 0; k < 60; k++) cout << "═";
            cout << "╝";
            mostrarBarras(arr, maxVal, j, i);
            this_thread::sleep_for(chrono::milliseconds(msDelay));
            
            if (arr[j] > clave) {
                arr[j + 1] = arr[j];
                intercambios++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = clave;
    }
    
    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
    
    limpiarPantalla();
    mostrarEncabezado("✓ INSERCIÓN COMPLETADO");
    cout << "║ Tiempo total: " << setw(46) << (to_string(duracion.count()) + " ms") << "║\n";
    cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
    cout << "║ Intercambios: " << setw(45) << intercambios << "║\n";
    cout << "╚";
    for (int i = 0; i < 60; i++) cout << "═";
    cout << "╝\n";
    mostrarBarras(arr, maxVal, -1, -1);
}

// ===== QUICK SORT =====
int particion(vector<int>& arr, int inicio, int fin, int maxVal) {
    int pivot = arr[fin];
    int i = inicio - 1;
    
    for (int j = inicio; j < fin; j++) {
        comparaciones++;
        
        limpiarPantalla();
        mostrarEncabezado("QUICK SORT - Particionando");
        cout << "║ Comparar arr[" << j << "]=" << arr[j] << " < Pivot[" << fin << "]=" << pivot;
        cout << setw(17) << "║\n";
        cout << "║ Resultado: ";
        if (arr[j] < pivot) {
            cout << arr[j] << " < " << pivot << " (MENOR - MOVER IZQUIERDA)" << setw(8) << "║\n";
        } else {
            cout << arr[j] << " >= " << pivot << " (NO MENOR - DEJAR)" << setw(17) << "║\n";
        }
        cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
        cout << "║ Intercambios: " << setw(45) << intercambios << "║\n";
        cout << "╚";
        for (int idx = 0; idx < 60; idx++) cout << "═";
        cout << "╝";
        mostrarBarras(arr, maxVal, j, fin, "Comparando con pivot");
        this_thread::sleep_for(chrono::milliseconds(msDelay));
        
        if (arr[j] < pivot) {
            i++;
            
            limpiarPantalla();
            mostrarEncabezado("QUICK SORT - INTERCAMBIANDO");
            cout << "║ Intercambiar arr[" << i << "]=" << arr[i] << " ↔ arr[" << j << "]=" << arr[j];
            cout << setw(15) << "║\n";
            cout << "║ Intercambios: " << setw(45) << (intercambios + 1) << "║\n";
            cout << "╚";
            for (int idx = 0; idx < 60; idx++) cout << "═";
            cout << "╝";
            mostrarBarras(arr, maxVal, i, j, "Intercambiando elementos");
            this_thread::sleep_for(chrono::milliseconds(msDelay));
            
            swap(arr[i], arr[j]);
            intercambios++;
        }
    }
    
    limpiarPantalla();
    mostrarEncabezado("QUICK SORT - Colocando pivot");
    cout << "║ Intercambiar arr[" << (i + 1) << "]=" << arr[i + 1] << " ↔ pivot[" << fin << "]=" << pivot;
    cout << setw(13) << "║\n";
    cout << "║ Pivot en posición final: " << (i + 1) << setw(33) << "║\n";
    cout << "╚";
    for (int idx = 0; idx < 60; idx++) cout << "═";
    cout << "╝";
    mostrarBarras(arr, maxVal, i + 1, fin, "Colocando pivot en posición");
    this_thread::sleep_for(chrono::milliseconds(msDelay));
    
    swap(arr[i + 1], arr[fin]);
    intercambios++;
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int inicio, int fin, int maxVal) {
    if (inicio < fin) {
        int pi = particion(arr, inicio, fin, maxVal);
        quickSortHelper(arr, inicio, pi - 1, maxVal);
        quickSortHelper(arr, pi + 1, fin, maxVal);
    }
}

void quickSort(vector<int> arr) {
    comparaciones = 0;
    intercambios = 0;
    int maxVal = *max_element(arr.begin(), arr.end());
    
    auto inicio = chrono::high_resolution_clock::now();
    quickSortHelper(arr, 0, arr.size() - 1, maxVal);
    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
    
    limpiarPantalla();
    mostrarEncabezado("✓ QUICK SORT COMPLETADO");
    cout << "║ Tiempo total: " << setw(46) << (to_string(duracion.count()) + " ms") << "║\n";
    cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
    cout << "║ Intercambios: " << setw(45) << intercambios << "║\n";
    cout << "╚";
    for (int i = 0; i < 60; i++) cout << "═";
    cout << "╝\n";
    mostrarBarras(arr, maxVal, -1, -1, "Ordenamiento completado");
}

// ===== MERGE SORT =====
void merge(vector<int>& arr, int inicio, int medio, int fin, int maxVal) {
    vector<int> izq(arr.begin() + inicio, arr.begin() + medio + 1);
    vector<int> der(arr.begin() + medio + 1, arr.begin() + fin + 1);
    
    int i = 0, j = 0, k = inicio;
    
    while (i < izq.size() && j < der.size()) {
        comparaciones++;
        
        limpiarPantalla();
        mostrarEncabezado("MERGE SORT - Fusionando");
        cout << "║ Comparando izq[" << i << "]=" << izq[i] << " vs der[" << j << "]=" << der[j];
        cout << setw(23) << "║\n";
        cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
        cout << "║ Intercambios: " << setw(45) << intercambios << "║\n";
        cout << "╚";
        for (int idx = 0; idx < 60; idx++) cout << "═";
        cout << "╝";
        
        if (izq[i] <= der[j]) {
            arr[k++] = izq[i++];
            mostrarBarras(arr, maxVal, k - 1, -1, "Copiando izquierda");
        } else {
            arr[k++] = der[j++];
            mostrarBarras(arr, maxVal, k - 1, -1, "Copiando derecha");
        }
        intercambios++;
        this_thread::sleep_for(chrono::milliseconds(msDelay));
    }
    
    while (i < izq.size()) {
        comparaciones++;
        arr[k++] = izq[i++];
        intercambios++;
        
        limpiarPantalla();
        mostrarEncabezado("MERGE SORT - Fusionando (resto izq)");
        cout << "║ Copiando elemento izq[" << (i - 1) << "]=" << arr[k - 1];
        cout << setw(29) << "║\n";
        cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
        cout << "║ Intercambios: " << setw(45) << intercambios << "║\n";
        cout << "╚";
        for (int idx = 0; idx < 60; idx++) cout << "═";
        cout << "╝";
        mostrarBarras(arr, maxVal, k - 1, -1, "Copiando resto izquierda");
        this_thread::sleep_for(chrono::milliseconds(msDelay));
    }
    
    while (j < der.size()) {
        comparaciones++;
        arr[k++] = der[j++];
        intercambios++;
        
        limpiarPantalla();
        mostrarEncabezado("MERGE SORT - Fusionando (resto der)");
        cout << "║ Copiando elemento der[" << (j - 1) << "]=" << arr[k - 1];
        cout << setw(29) << "║\n";
        cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
        cout << "║ Intercambios: " << setw(45) << intercambios << "║\n";
        cout << "╚";
        for (int idx = 0; idx < 60; idx++) cout << "═";
        cout << "╝";
        mostrarBarras(arr, maxVal, k - 1, -1, "Copiando resto derecha");
        this_thread::sleep_for(chrono::milliseconds(msDelay));
    }
}

void mergeSortHelper(vector<int>& arr, int inicio, int fin, int maxVal) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;
        mergeSortHelper(arr, inicio, medio, maxVal);
        mergeSortHelper(arr, medio + 1, fin, maxVal);
        merge(arr, inicio, medio, fin, maxVal);
    }
}

void mergeSort(vector<int> arr) {
    comparaciones = 0;
    intercambios = 0;
    int maxVal = *max_element(arr.begin(), arr.end());
    
    auto inicio = chrono::high_resolution_clock::now();
    mergeSortHelper(arr, 0, arr.size() - 1, maxVal);
    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
    
    limpiarPantalla();
    mostrarEncabezado("✓ MERGE SORT COMPLETADO");
    cout << "║ Tiempo total: " << setw(46) << (to_string(duracion.count()) + " ms") << "║\n";
    cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
    cout << "║ Intercambios: " << setw(45) << intercambios << "║\n";
    cout << "╚";
    for (int i = 0; i < 60; i++) cout << "═";
    cout << "╝\n";
    mostrarBarras(arr, maxVal, -1, -1, "Ordenamiento completado");
}

// ===== HEAP SORT =====
void heapify(vector<int>& arr, int size, int i, int maxVal) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < size) {
        comparaciones++;
        limpiarPantalla();
        mostrarEncabezado("HEAP SORT - Comparando");
        cout << "║ Padre[" << i << "]=" << arr[i] << " vs HijoIzq[" << left << "]=" << arr[left];
        cout << setw(18) << "║\n";
        cout << "║ Resultado: ";
        if (arr[left] > arr[largest]) {
            cout << arr[left] << " > " << arr[largest] << " (ACTUAL MAYOR)" << setw(15) << "║\n";
            largest = left;
        } else {
            cout << arr[left] << " <= " << arr[largest] << " (NO MAYOR)" << setw(17) << "║\n";
        }
        cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
        cout << "╚";
        for (int idx = 0; idx < 60; idx++) cout << "═";
        cout << "╝";
        mostrarBarras(arr, maxVal, i, left, "Comparando hijo izquierdo");
        this_thread::sleep_for(chrono::milliseconds(msDelay));
    }
    
    if (right < size) {
        comparaciones++;
        limpiarPantalla();
        mostrarEncabezado("HEAP SORT - Comparando");
        cout << "║ Actual[" << largest << "]=" << arr[largest] << " vs HijoDer[" << right << "]=" << arr[right];
        cout << setw(17) << "║\n";
        cout << "║ Resultado: ";
        if (arr[right] > arr[largest]) {
            cout << arr[right] << " > " << arr[largest] << " (NUEVA MAYOR)" << setw(14) << "║\n";
            largest = right;
        } else {
            cout << arr[right] << " <= " << arr[largest] << " (NO MAYOR)" << setw(16) << "║\n";
        }
        cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
        cout << "╚";
        for (int idx = 0; idx < 60; idx++) cout << "═";
        cout << "╝";
        mostrarBarras(arr, maxVal, largest, right, "Comparando hijo derecho");
        this_thread::sleep_for(chrono::milliseconds(msDelay));
    }
    
    if (largest != i) {
        limpiarPantalla();
        mostrarEncabezado("HEAP SORT - INTERCAMBIANDO");
        cout << "║ Intercambiar arr[" << i << "]=" << arr[i] << " ↔ arr[" << largest << "]=" << arr[largest];
        cout << setw(15) << "║\n";
        cout << "║ Intercambios: " << setw(45) << (intercambios + 1) << "║\n";
        cout << "╚";
        for (int idx = 0; idx < 60; idx++) cout << "═";
        cout << "╝";
        mostrarBarras(arr, maxVal, i, largest, "Intercambiando elementos");
        this_thread::sleep_for(chrono::milliseconds(msDelay));
        
        swap(arr[i], arr[largest]);
        intercambios++;
        heapify(arr, size, largest, maxVal);
    }
}

void heapSort(vector<int> arr) {
    comparaciones = 0;
    intercambios = 0;
    int maxVal = *max_element(arr.begin(), arr.end());
    int n = arr.size();
    
    auto inicio = chrono::high_resolution_clock::now();
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, maxVal);
    }
    
    for (int i = n - 1; i > 0; i--) {
        limpiarPantalla();
        mostrarEncabezado("HEAP SORT - Extrayendo máximo");
        cout << "║ Intercambiar raíz[0]=" << arr[0] << " ↔ final[" << i << "]=" << arr[i];
        cout << setw(16) << "║\n";
        cout << "║ Iteración: " << setw(49) << (to_string(n - i) + "/" + to_string(n - 1)) << "║\n";
        cout << "╚";
        for (int idx = 0; idx < 60; idx++) cout << "═";
        cout << "╝";
        mostrarBarras(arr, maxVal, 0, i, "Intercambiando raíz con final");
        this_thread::sleep_for(chrono::milliseconds(msDelay));
        
        swap(arr[0], arr[i]);
        intercambios++;
        heapify(arr, i, 0, maxVal);
    }
    
    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
    
    limpiarPantalla();
    mostrarEncabezado("✓ HEAP SORT COMPLETADO");
    cout << "║ Tiempo total: " << setw(46) << (to_string(duracion.count()) + " ms") << "║\n";
    cout << "║ Comparaciones: " << setw(44) << comparaciones << "║\n";
    cout << "║ Intercambios: " << setw(45) << intercambios << "║\n";
    cout << "╚";
    for (int i = 0; i < 60; i++) cout << "═";
    cout << "╝\n";
    mostrarBarras(arr, maxVal, -1, -1, "Ordenamiento completado");
}

// ===== VERSIONES SIN VISUALIZACIÓN (PARA COMPARACIÓN RÁPIDA) =====
void burbujaRapido(vector<int> arr, ResAlgoritmo& res) {
    int compare = 0, interc = 0;
    int n = arr.size();
    auto inicio = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            compare++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                interc++;
            }
        }
    }
    
    auto fin = chrono::high_resolution_clock::now();
    res.tiempo = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();
    res.compars = compare;
    res.intercam = interc;
}

void insercionRapido(vector<int> arr, ResAlgoritmo& res) {
    int compare = 0, interc = 0;
    int n = arr.size();
    auto inicio = chrono::high_resolution_clock::now();
    
    for (int i = 1; i < n; i++) {
        int clave = arr[i];
        int j = i - 1;
        while (j >= 0) {
            compare++;
            if (arr[j] > clave) {
                arr[j + 1] = arr[j];
                interc++;
                j--;
            } else break;
        }
        arr[j + 1] = clave;
    }
    
    auto fin = chrono::high_resolution_clock::now();
    res.tiempo = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();
    res.compars = compare;
    res.intercam = interc;
}

int particionRapido(vector<int>& arr, int inicio, int fin, int& compare, int& interc) {
    int pivot = arr[fin];
    int i = inicio - 1;
    for (int j = inicio; j < fin; j++) {
        compare++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            interc++;
        }
    }
    swap(arr[i + 1], arr[fin]);
    interc++;
    return i + 1;
}

void quickSortRapidoHelper(vector<int>& arr, int inicio, int fin, int& compare, int& interc) {
    if (inicio < fin) {
        int pi = particionRapido(arr, inicio, fin, compare, interc);
        quickSortRapidoHelper(arr, inicio, pi - 1, compare, interc);
        quickSortRapidoHelper(arr, pi + 1, fin, compare, interc);
    }
}

void quickSortRapido(vector<int> arr, ResAlgoritmo& res) {
    int compare = 0, interc = 0;
    auto inicio = chrono::high_resolution_clock::now();
    quickSortRapidoHelper(arr, 0, arr.size() - 1, compare, interc);
    auto fin = chrono::high_resolution_clock::now();
    
    res.tiempo = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();
    res.compars = compare;
    res.intercam = interc;
}

void mergeRapido(vector<int>& arr, int inicio, int medio, int fin, int& compare, int& interc) {
    vector<int> izq(arr.begin() + inicio, arr.begin() + medio + 1);
    vector<int> der(arr.begin() + medio + 1, arr.begin() + fin + 1);
    int i = 0, j = 0, k = inicio;
    
    while (i < izq.size() && j < der.size()) {
        compare++;
        if (izq[i] <= der[j]) arr[k++] = izq[i++];
        else arr[k++] = der[j++];
        interc++;
    }
    while (i < izq.size()) { arr[k++] = izq[i++]; interc++; }
    while (j < der.size()) { arr[k++] = der[j++]; interc++; }
}

void mergeSortRapidoHelper(vector<int>& arr, int inicio, int fin, int& compare, int& interc) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;
        mergeSortRapidoHelper(arr, inicio, medio, compare, interc);
        mergeSortRapidoHelper(arr, medio + 1, fin, compare, interc);
        mergeRapido(arr, inicio, medio, fin, compare, interc);
    }
}

void mergeSortRapido(vector<int> arr, ResAlgoritmo& res) {
    int compare = 0, interc = 0;
    auto inicio = chrono::high_resolution_clock::now();
    mergeSortRapidoHelper(arr, 0, arr.size() - 1, compare, interc);
    auto fin = chrono::high_resolution_clock::now();
    
    res.tiempo = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();
    res.compars = compare;
    res.intercam = interc;
}

void heapifyRapido(vector<int>& arr, int size, int i, int& compare, int& interc) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < size) {
        compare++;
        if (arr[left] > arr[largest]) largest = left;
    }
    if (right < size) {
        compare++;
        if (arr[right] > arr[largest]) largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        interc++;
        heapifyRapido(arr, size, largest, compare, interc);
    }
}

void heapSortRapido(vector<int> arr, ResAlgoritmo& res) {
    int compare = 0, interc = 0;
    int n = arr.size();
    auto inicio = chrono::high_resolution_clock::now();
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyRapido(arr, n, i, compare, interc);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        interc++;
        heapifyRapido(arr, i, 0, compare, interc);
    }
    
    auto fin = chrono::high_resolution_clock::now();
    res.tiempo = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();
    res.compars = compare;
    res.intercam = interc;
}

void compararTodos(vector<int> arreglo) {
    vector<ResAlgoritmo> resultados(5);
    resultados[0].nombre = "Burbuja";
    resultados[1].nombre = "Inserción";
    resultados[2].nombre = "Quick Sort";
    resultados[3].nombre = "Merge Sort";
    resultados[4].nombre = "Heap Sort";
    
    limpiarPantalla();
    cout << "\n⏳ Ejecutando todos los algoritmos (sin visualización)...\n\n";
    
    burbujaRapido(arreglo, resultados[0]);
    cout << "✓ Burbuja completado - " << resultados[0].tiempo << " ms\n";
    
    insercionRapido(arreglo, resultados[1]);
    cout << "✓ Inserción completado - " << resultados[1].tiempo << " ms\n";
    
    quickSortRapido(arreglo, resultados[2]);
    cout << "✓ Quick Sort completado - " << resultados[2].tiempo << " ms\n";
    
    mergeSortRapido(arreglo, resultados[3]);
    cout << "✓ Merge Sort completado - " << resultados[3].tiempo << " ms\n";
    
    heapSortRapido(arreglo, resultados[4]);
    cout << "✓ Heap Sort completado - " << resultados[4].tiempo << " ms\n";
    
    // Mostrar comparación
    limpiarPantalla();
    cout << "\n╔════════════════════════════════════════════════════════════════╗\n";
    cout << "║        COMPARACIÓN DE TIEMPOS - TODOS LOS ALGORITMOS          ║\n";
    cout << "╚════════════════════════════════════════════════════════════════╝\n\n";
    
    cout << "┌─────────────┬──────────────┬────────────────┬──────────────┐\n";
    cout << "│ Algoritmo   │ Tiempo (ms)  │ Comparaciones  │ Intercambios │\n";
    cout << "├─────────────┼──────────────┼────────────────┼──────────────┤\n";
    
    long long minTiempo = resultados[0].tiempo;
    for (const auto& r : resultados) {
        if (r.tiempo < minTiempo) minTiempo = r.tiempo;
    }
    
    for (const auto& r : resultados) {
        cout << "│ " << setw(11) << left << r.nombre << "│ ";
        cout << setw(12) << right << r.tiempo << " │ ";
        cout << setw(14) << right << r.compars << " │ ";
        cout << setw(12) << right << r.intercam << " │";
        
        if (r.tiempo == minTiempo && r.tiempo > 0) {
            cout << " ⭐ RÁPIDO";
        }
        cout << "\n";
    }
    
    cout << "└─────────────┴──────────────┴────────────────┴──────────────┘\n";
    cout << "\nVelocidad relativa (factor):\n";
    
    long long maxTiempo = resultados[0].tiempo;
    for (const auto& r : resultados) {
        if (r.tiempo > maxTiempo) maxTiempo = r.tiempo;
    }
    
    for (const auto& r : resultados) {
        if (minTiempo > 0) {
            double factor = (double)r.tiempo / minTiempo;
            cout << "  " << setw(12) << left << r.nombre << ": " << fixed << setprecision(2) << factor << "x";
            if (r.tiempo == minTiempo) cout << " (referencia)";
            cout << "\n";
        }
    }
    
    cout << "\nPresione Enter para volver al menú...\n";
    cin.ignore();
    cin.get();
}

// ===== MENÚ PRINCIPAL =====
int main() {
    srand(time(0));
    int tamano = 0;
    
    limpiarPantalla();
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║     COMPARADOR DE ALGORITMOS DE ORDEN      ║\n";
    cout << "║      Visualización en Tiempo Real          ║\n";
    cout << "╚════════════════════════════════════════════╝\n\n";
    
    cout << "Ingrese el tamaño del arreglo (10-30 recomendado): ";
    cin >> tamano;
    
    if (tamano < 5 || tamano > 100) {
        tamano = 20;
        cout << "Tamaño inválido. Se usará 20.\n";
    }
    
    char permitirRep;
    cout << "¿Permitir números repetidos? (s/n): ";
    cin >> permitirRep;
    permitirRepetidos = (permitirRep == 's' || permitirRep == 'S');
    
    vector<int> arreglo = generarArreglo(tamano, permitirRepetidos);
    
    cout << "\nArreglo generado. Presione Enter para continuar...\n";
    cin.ignore();
    cin.get();
    
    bool continuar = true;
    while (continuar) {
        limpiarPantalla();
        cout << "╔════════════════════════════════════════════╗\n";
        cout << "║          SELECCIONE UN ALGORITMO           ║\n";
        cout << "╚════════════════════════════════════════════╝\n\n";
        cout << "1. Burbuja\n";
        cout << "2. Inserción\n";
        cout << "3. Quick Sort\n";
        cout << "4. Merge Sort\n";
        cout << "5. Heap Sort\n";
        cout << "6. Cambiar velocidad (actualmente " << msDelay << " ms)\n";
        cout << "7. Generar nuevo arreglo (";
        cout << (permitirRepetidos ? "con" : "sin");
        cout << " repetidos)\n";
        cout << "8. Comparar TODOS los algoritmos\n";
        cout << "0. Salir\n\n";
        cout << "Opción: ";
        
        int opcion;
        cin >> opcion;
        
        limpiarPantalla();
        cout << "Ejecutando algoritmo...\n\n";
        
        switch (opcion) {
            case 1:
                burbuja(arreglo);
                break;
            case 2:
                insercion(arreglo);
                break;
            case 3:
                quickSort(arreglo);
                break;
            case 4:
                mergeSort(arreglo);
                break;
            case 5:
                heapSort(arreglo);
                break;
            case 6: {
                cout << "Velocidad actual: " << msDelay << " ms\n";
                cout << "Nueva velocidad (0-300 ms): ";
                cin >> msDelay;
                cout << "¡Velocidad actualizada!\n";
                cout << "Presione Enter para volver al menú...\n";
                cin.ignore();
                cin.get();
                continue;
            }
            case 7: {
                char permitirRep;
                cout << "¿Permitir números repetidos? (s/n): ";
                cin >> permitirRep;
                permitirRepetidos = (permitirRep == 's' || permitirRep == 'S');
                arreglo = generarArreglo(tamano, permitirRepetidos);
                cout << "¡Nuevo arreglo generado!\n";
                cout << "Presione Enter para volver al menú...\n";
                cin.ignore();
                cin.get();
                continue;
            }
            case 8:
                compararTodos(arreglo);
                continue;
            case 0:
                continuar = false;
                limpiarPantalla();
                cout << "\n¡Gracias por usar el comparador!\n\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
        
        if (continuar && opcion >= 1 && opcion <= 5) {
            cout << "\nPresione Enter para volver al menú...\n";
            cin.ignore();
            cin.get();
        }
    }
    
    return 0;
}
