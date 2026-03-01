#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int pasoActual = 1;

void imprimirArreglo(const vector<int>& arr, int size = -1, int i = -1, int left = -1, int right = -1, int largest = -1) {
    if (size == -1) size = arr.size();
    
    cout << "  [ ";
    for (int idx = 0; idx < size; idx++) {
        int colores = 0;
        bool esI = (i != -1 && idx == i);
        bool esLeft = (left != -1 && idx == left);
        bool esRight = (right != -1 && idx == right);
        bool esLargest = (largest != -1 && idx == largest);
        
        if (esI && esLargest) {
            cout << "\033[1;36m" << arr[idx] << "(i,L)\033[0m"; // Cyan
        } else if (esI && esLeft) {
            cout << "\033[1;32m" << arr[idx] << "(i,l)\033[0m"; // Verde
        } else if (esI && esRight) {
            cout << "\033[1;33m" << arr[idx] << "(i,r)\033[0m"; // Amarillo
        } else if (esI) {
            cout << "\033[1;35m" << arr[idx] << "(i)\033[0m"; // Magenta
        } else if (esLargest) {
            cout << "\033[1;31m" << arr[idx] << "(L)\033[0m"; // Rojo
        } else if (esLeft) {
            cout << "\033[1;32m" << arr[idx] << "(l)\033[0m"; // Verde
        } else if (esRight) {
            cout << "\033[1;33m" << arr[idx] << "(r)\033[0m"; // Amarillo
        } else {
            cout << arr[idx];
        }
        if (idx < size - 1) cout << ", ";
    }
    cout << " ]";
    
    if (size < arr.size()) {
        cout << " \033[90m";
        for (int idx = size; idx < arr.size(); idx++) {
            cout << ", " << arr[idx];
        }
        cout << "\033[0m";
    }
    cout << "\n";
}

void mostrarArbolHeap(const vector<int>& arr, int size) {
    cout << "\n  Estructura de Heap (árbol binario):\n";
    int nivel = 1;
    int elementos_en_nivel = 1;
    int indice = 0;
    
    while (indice < size) {
        cout << "  Nivel " << (nivel - 1) << ": ";
        for (int j = 0; j < elementos_en_nivel && indice < size; j++) {
            cout << arr[indice];
            if (indice < size - 1) cout << " ";
            indice++;
        }
        cout << "\n";
        nivel++;
        elementos_en_nivel *= 2;
    }
    cout << "\n";
}

void heapify(vector<int>& arr, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    cout << "\n  HEAPIFY en indice " << i << " (valor=" << arr[i] << ")\n";
    cout << "  Nodo i=" << i << ", hijo izquierda=" << left << ", hijo derecha=" << right << "\n";
    cout << "  Arreglo actual: ";
    imprimirArreglo(arr, size, i, left, right, -1);
    
    if (left < size) {
        cout << "    Comparar arr[" << i << "]=" << arr[i] << " con arr[" << left << "]=" << arr[left];
        if (arr[left] > arr[largest]) {
            cout << " -> " << arr[left] << " > " << arr[largest] << " (VERDADERO)\n";
            cout << "    largest se actualiza a " << left << "\n";
            largest = left;
        } else {
            cout << " -> " << arr[left] << " <= " << arr[largest] << " (FALSO)\n";
        }
    }

    if (right < size) {
        cout << "    Comparar arr[" << largest << "]=" << arr[largest] << " con arr[" << right << "]=" << arr[right];
        if (arr[right] > arr[largest]) {
            cout << " -> " << arr[right] << " > " << arr[largest] << " (VERDADERO)\n";
            cout << "    largest se actualiza a " << right << "\n";
            largest = right;
        } else {
            cout << " -> " << arr[right] << " <= " << arr[largest] << " (FALSO)\n";
        }
    }

    if (largest != i) {
        cout << "    INTERCAMBIAR arr[" << i << "]=" << arr[i] << " con arr[" << largest << "]=" << arr[largest] << "\n";
        swap(arr[i], arr[largest]);
        cout << "    Arreglo después de intercambio: ";
        imprimirArreglo(arr, size, largest, -1, -1, -1);
        heapify(arr, size, largest);
    } else {
        cout << "    No hay intercambio necesario\n";
    }
}

void heapSort(vector<int>& arr) {
    int size = arr.size();
    
    cout << "\nArreglo Original: ";
    imprimirArreglo(arr);
    
    cout << "\n" << string(70, '=') << "\n";
    cout << "FASE 1: CONSTRUIR MAX HEAP\n";
    cout << string(70, '=') << "\n";
    
    for (int i = size / 2 - 1; i >= 0; i--) {
        cout << "\nPASO " << pasoActual++ << ": Heapify desde indice " << i << "\n";
        heapify(arr, size, i);
    }
    
    cout << "\n" << string(70, '=') << "\n";
    cout << "MAX HEAP CONSTRUIDO:\n";
    cout << string(70, '=') << "\n";
    cout << "Arreglo actual: ";
    imprimirArreglo(arr);
    mostrarArbolHeap(arr, size);
    
    cout << "\n" << string(70, '=') << "\n";
    cout << "FASE 2: EXTRAER ELEMENTOS DEL HEAP\n";
    cout << string(70, '=') << "\n";
    
    for (int i = size - 1; i > 0; i--) {
        cout << "\nPASO " << pasoActual++ << ": Extraer maximo y heapify\n";
        cout << "  INTERCAMBIAR arr[0]=" << arr[0] << " (maximo) con arr[" << i << "]=" << arr[i] << "\n";
        swap(arr[0], arr[i]);
        cout << "  Arreglo después de intercambio: ";
        imprimirArreglo(arr, i + 1);
        cout << "  Elemento ordenado (al final): " << arr[i] << "\n";
        
        cout << "  Heapify el nuevo raiz (indice 0):\n";
        heapify(arr, i, 0);
    }
    
    cout << "\n" << string(70, '=') << "\n";
    cout << "ARREGLO FINAL ORDENADO: ";
    imprimirArreglo(arr);
    cout << string(70, '=') << "\n\n";
}

int main() {
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║    ALGORITMO HEAP SORT - PASO A PASO        ║\n";
    cout << "║                                            ║\n";
    cout << "║  (i) = Indice nodo actual                 ║\n";
    cout << "║  (l) = Indice hijo izquierdo              ║\n";
    cout << "║  (r) = Indice hijo derecho                ║\n";
    cout << "║  (L) = Indice del elemento más grande     ║\n";
    cout << "║                                            ║\n";
    cout << "║  FASE 1: Construir Max Heap               ║\n";
    cout << "║  FASE 2: Extraer y ordenar                ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    
    vector<int> arr = {54, 37, 81, 12, 95, 6, 23, 68, 47, 76, 29, 42};
    
    heapSort(arr);
    
    return 0;
}
