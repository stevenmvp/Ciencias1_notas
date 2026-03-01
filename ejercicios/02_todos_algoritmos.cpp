#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

long long pasos_burbuja = 0;
long long pasos_quick = 0;
long long pasos_merge = 0;
long long pasos_heap = 0;

// ===== BURBUJA =====
void burbuja(int arr[], int n) {
    pasos_burbuja = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            pasos_burbuja++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ===== QUICKSORT =====
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        pasos_quick++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ===== MERGESORT =====
void merge(int arr[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    int temp[1000];
    
    while (i <= mid && j <= right) {
        pasos_merge++;
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        pasos_merge++;
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        pasos_merge++;
        temp[k++] = arr[j++];
    }
    
    for (int i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ===== HEAPSORT =====
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n) {
        pasos_heap++;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }
    
    if (right < n) {
        pasos_heap++;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }
    
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    pasos_heap = 0;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// ===== FUNCIONES AUXILIARES =====
void mostrarArreglo(int arr[], int n, string titulo = "") {
    if (!titulo.empty()) {
        cout << titulo;
    }
    for (int i = 0; i < (n < 10 ? n : 10); i++) {
        cout << arr[i] << " ";
    }
    if (n > 10) cout << "...";
    cout << endl;
}

void copiarArreglo(int origen[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

int main() {
    int opc = 0;
    int n = 0;
    int arr[1000], arr_aux[1000];
    
    cout << "===== ALGORITMOS DE ORDENAMIENTO =====" << endl;
    cout << "\n0 - Ingresar numeros manualmente" << endl;
    cout << "1 - Generar numeros aleatorios" << endl;
    cout << "Opcion: ";
    cin >> opc;
    
    if (opc == 0) {
        cout << "Ingresa el numero de elementos: ";
        cin >> n;
        cout << "Ingresa los " << n << " numeros: ";
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    } else if (opc == 1) {
        cout << "Ingresa el numero de elementos: ";
        cin >> n;
        srand(time(0));
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000 + 1;
        }
    }
    
    mostrarArreglo(arr, n, "Arreglo Original: ");
    
    cout << "\n===== SELECCIONA ALGORITMO =====" << endl;
    cout << "0 - Burbuja" << endl;
    cout << "1 - Quick Sort" << endl;
    cout << "2 - Merge Sort" << endl;
    cout << "3 - Heap Sort" << endl;
    cout << "4 - Comparar TODOS" << endl;
    cout << "Opcion: ";
    cin >> opc;
    
    if (opc == 0) {
        // BURBUJA
        copiarArreglo(arr, arr_aux, n);
        cout << "\n--- EJECUTANDO BURBUJA ---" << endl;
        burbuja(arr_aux, n);
        mostrarArreglo(arr_aux, n, "Arreglo Ordenado: ");
        cout << "Pasos (comparaciones): " << pasos_burbuja << endl;
        cout << "Complejidad Teórica: O(n²)" << endl;
    }
    else if (opc == 1) {
        // QUICKSORT
        copiarArreglo(arr, arr_aux, n);
        cout << "\n--- EJECUTANDO QUICK SORT ---" << endl;
        pasos_quick = 0;
        quickSort(arr_aux, 0, n - 1);
        mostrarArreglo(arr_aux, n, "Arreglo Ordenado: ");
        cout << "Pasos (comparaciones): " << pasos_quick << endl;
        cout << "Complejidad Teórica: O(n log n)" << endl;
    }
    else if (opc == 2) {
        // MERGESORT
        copiarArreglo(arr, arr_aux, n);
        cout << "\n--- EJECUTANDO MERGE SORT ---" << endl;
        pasos_merge = 0;
        mergeSort(arr_aux, 0, n - 1);
        mostrarArreglo(arr_aux, n, "Arreglo Ordenado: ");
        cout << "Pasos (comparaciones): " << pasos_merge << endl;
        cout << "Complejidad Teórica: O(n log n)" << endl;
    }
    else if (opc == 3) {
        // HEAPSORT
        copiarArreglo(arr, arr_aux, n);
        cout << "\n--- EJECUTANDO HEAP SORT ---" << endl;
        heapSort(arr_aux, n);
        mostrarArreglo(arr_aux, n, "Arreglo Ordenado: ");
        cout << "Pasos (comparaciones): " << pasos_heap << endl;
        cout << "Complejidad Teórica: O(n log n)" << endl;
    }
    else if (opc == 4) {
        // COMPARAR TODOS
        int arr_b[1000], arr_q[1000], arr_m[1000], arr_h[1000];
        
        copiarArreglo(arr, arr_b, n);
        copiarArreglo(arr, arr_q, n);
        copiarArreglo(arr, arr_m, n);
        copiarArreglo(arr, arr_h, n);
        
        cout << "\n--- EJECUTANDO TODOS LOS ALGORITMOS ---" << endl;
        
        burbuja(arr_b, n);
        
        pasos_quick = 0;
        quickSort(arr_q, 0, n - 1);
        
        pasos_merge = 0;
        mergeSort(arr_m, 0, n - 1);
        
        heapSort(arr_h, n);
        
        // Mostrar tabla de comparación
        cout << "\n" << string(80, '=') << endl;
        cout << "COMPARACION DE ALGORITMOS" << endl;
        cout << string(80, '=') << endl;
        
        cout << "\nElementos a ordenar: " << n << endl << endl;
        
        cout << setw(18) << "Algoritmo" 
             << setw(20) << "Pasos" 
             << setw(20) << "Complejidad"
             << setw(22) << "Arreglo válido" << endl;
        cout << string(80, '-') << endl;
        
        bool b_ok = true, q_ok = true, m_ok = true, h_ok = true;
        for (int i = 0; i < n - 1; i++) {
            if (arr_b[i] > arr_b[i+1]) b_ok = false;
            if (arr_q[i] > arr_q[i+1]) q_ok = false;
            if (arr_m[i] > arr_m[i+1]) m_ok = false;
            if (arr_h[i] > arr_h[i+1]) h_ok = false;
        }
        
        cout << setw(18) << "Burbuja" 
             << setw(20) << pasos_burbuja 
             << setw(20) << "O(n²)"
             << setw(22) << (b_ok ? "✓ Correcto" : "✗ Error") << endl;
        
        cout << setw(18) << "Quick Sort" 
             << setw(20) << pasos_quick 
             << setw(20) << "O(n log n)"
             << setw(22) << (q_ok ? "✓ Correcto" : "✗ Error") << endl;
        
        cout << setw(18) << "Merge Sort" 
             << setw(20) << pasos_merge 
             << setw(20) << "O(n log n)"
             << setw(22) << (m_ok ? "✓ Correcto" : "✗ Error") << endl;
        
        cout << setw(18) << "Heap Sort" 
             << setw(20) << pasos_heap 
             << setw(20) << "O(n log n)"
             << setw(22) << (h_ok ? "✓ Correcto" : "✗ Error") << endl;
        
        cout << string(80, '=') << endl;
        
        // Análisis
        cout << "\n=== ANALISIS ===" << endl;
        
        long long minimo = pasos_quick;
        string mas_rapido = "Quick Sort";
        
        if (pasos_merge < minimo) {
            minimo = pasos_merge;
            mas_rapido = "Merge Sort";
        }
        if (pasos_heap < minimo) {
            minimo = pasos_heap;
            mas_rapido = "Heap Sort";
        }
        
        cout << "\nAlgoritmo mas eficiente (menos pasos):" << endl;
        cout << "  -> " << mas_rapido << " (" << minimo << " pasos)" << endl;
        
        cout << "\nAlgoritmo menos eficiente (mas pasos):" << endl;
        cout << "  -> Burbuja (" << pasos_burbuja << " pasos)" << endl;
        
        cout << "\nComparativas de velocidad:" << endl;
        cout << "  Burbuja vs Quick: " << fixed << setprecision(2) 
             << pasos_burbuja / (double)pasos_quick << "x mas lento" << endl;
        cout << "  Burbuja vs Merge: " << pasos_burbuja / (double)pasos_merge 
             << "x mas lento" << endl;
        cout << "  Burbuja vs Heap: " << pasos_burbuja / (double)pasos_heap 
             << "x mas lento" << endl;
        
        cout << "\n--- CONCLUSIONES ---" << endl;
        cout << "Para n=" << n << " elementos:" << endl;
        cout << "• Burbuja O(n²): " << pasos_burbuja << " operaciones" << endl;
        cout << "• Quick Sort O(n log n): " << pasos_quick << " operaciones" << endl;
        cout << "• Merge Sort O(n log n): " << pasos_merge << " operaciones" << endl;
        cout << "• Heap Sort O(n log n): " << pasos_heap << " operaciones" << endl;
    }
    
    return 0;
}
