#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int pasoActual = 1;

void imprimirArreglo(const vector<int>& arr, int inicio = -1, int fin = -1, int i = -1, int j = -1, int pivot = -1) {
    cout << "  [ ";
    for (int idx = 0; idx < arr.size(); idx++) {
        if (idx == pivot) {
            cout << "\033[1;33m" << arr[idx] << "(P)\033[0m"; // Amarillo para pivot
        } else if (idx == i) {
            cout << "\033[1;32m" << arr[idx] << "(i)\033[0m"; // Verde para i
        } else if (idx == j) {
            cout << "\033[1;31m" << arr[idx] << "(j)\033[0m"; // Rojo para j
        } else if (inicio != -1 && fin != -1 && idx >= inicio && idx <= fin) {
            cout << arr[idx];
        } else if (inicio == -1) {
            cout << arr[idx];
        } else {
            cout << "\033[90m" << arr[idx] << "\033[0m"; // Gris para fuera de rango
        }
        if (idx < arr.size() - 1) cout << ", ";
    }
    cout << " ]\n";
}

int particion(vector<int>& arr, int inicio, int fin) {
    int pivot = arr[fin];
    int i = inicio - 1;
    
    cout << "\n  >> PARTICIONANDO desde indice " << inicio << " hasta " << fin << "\n";
    cout << "  >> PIVOT seleccionado: " << pivot << " (en posicion " << fin << ")\n\n";
    
    for (int j = inicio; j < fin; j++) {
        cout << "  PASO " << pasoActual++ << ": ¿arr[" << j << "]=" << arr[j] 
             << " < pivot=" << pivot << "?";
        
        if (arr[j] < pivot) {
            cout << " -> VERDADERO\n";
            i++;
            cout << "     Incrementar i: i=" << i << "\n";
            cout << "     Intercambiar arr[" << i << "]=" << arr[i] 
                 << " con arr[" << j << "]=" << arr[j] << "\n";
            swap(arr[i], arr[j]);
            cout << "     Arreglo actual: ";
            imprimirArreglo(arr, inicio, fin, i, j, fin);
        } else {
            cout << " -> FALSO (no hay intercambio)\n";
            cout << "     Arreglo actual: ";
            imprimirArreglo(arr, inicio, fin, i, j, fin);
        }
        cout << "\n";
    }
    
    cout << "  PASO " << pasoActual++ << ": Colocar pivot en su posicion final\n";
    cout << "     i incrementado a: " << (i + 1) << "\n";
    cout << "     Intercambiar arr[" << (i + 1) << "] con arr[" << fin << "] (pivot)\n";
    swap(arr[i + 1], arr[fin]);
    cout << "     Arreglo actual: ";
    imprimirArreglo(arr, inicio, fin, i + 1, -1, i + 1);
    cout << "     Pivot " << pivot << " en posicion final: " << (i + 1) << "\n\n";
    
    return i + 1;
}

void quickSort(vector<int>& arr, int inicio, int fin, int nivel = 0) {
    if (inicio < fin) {
        string indentacion(nivel * 2, ' ');
        
        cout << indentacion << "\n=== NIVEL " << nivel << " ===\n";
        cout << indentacion << "Ordenando desde indice " << inicio << " hasta " << fin << "\n";
        cout << indentacion << "Arreglo actual: ";
        imprimirArreglo(arr);
        
        int pi = particion(arr, inicio, fin);
        
        cout << indentacion << "\n>>> RECURSION IZQUIERDA (indices " << inicio << " a " << (pi - 1) << ")\n";
        quickSort(arr, inicio, pi - 1, nivel + 1);
        
        cout << indentacion << "\n>>> RECURSION DERECHA (indices " << (pi + 1) << " a " << fin << ")\n";
        quickSort(arr, pi + 1, fin, nivel + 1);
    }
}

int main() {
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║      ALGORITMO QUICK SORT - PASO A PASO     ║\n";
    cout << "║                                            ║\n";
    cout << "║  (P) = Pivot                              ║\n";
    cout << "║  (i) = Indice izquierdo                   ║\n";
    cout << "║  (j) = Indice actual comparando           ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    
    cout << "\nArreglo Original: ";
    imprimirArreglo(arr);
    
    cout << "\n" << string(50, '=') << "\n";
    cout << "INICIO DEL ALGORITMO QUICK SORT\n";
    cout << string(50, '=') << "\n";
    
    quickSort(arr, 0, arr.size() - 1);
    
    cout << "\n" << string(50, '=') << "\n";
    cout << "ARREGLO FINAL ORDENADO: ";
    imprimirArreglo(arr);
    cout << string(50, '=') << "\n\n";
    
    return 0;
}
