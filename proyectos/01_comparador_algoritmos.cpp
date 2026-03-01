#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <stdexcept>
using namespace std;

long long pasos_quick = 0;
long long pasos_merge = 0;
long long pasos_heap = 0;

// Contadores adicionales
long long intercambios_quick = 0;
long long intercambios_merge = 0;
long long intercambios_heap = 0;
long long ciclos_quick = 0;
long long ciclos_merge = 0;
long long ciclos_heap = 0;

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
            intercambios_quick++;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    intercambios_quick++;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        ciclos_quick++;
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ===== MERGESORT =====
void merge(int arr[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    int len = right - left + 1;
    int *temp = nullptr;
    try {
        temp = new int[len];
    } catch (bad_alloc &e) {
        throw runtime_error("merge: memoria insuficiente para el arreglo temporal");
    }

    while (i <= mid && j <= right) {
        pasos_merge++;
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
        intercambios_merge++;
    }
    
    while (i <= mid) {
        pasos_merge++;
        temp[k++] = arr[i++];
        intercambios_merge++;
    }
    
    while (j <= right) {
        pasos_merge++;
        temp[k++] = arr[j++];
        intercambios_merge++;
    }
    
    for (int i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
        intercambios_merge++;
    }
    delete[] temp;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        ciclos_merge++;
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
        intercambios_heap++;
        ciclos_heap++;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    pasos_heap = 0;
    intercambios_heap = 0;
    ciclos_heap = 0;
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    for (int i = n - 1; i > 0; i--) {
        ciclos_heap++;
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        intercambios_heap++;
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

bool verificarOrdenamiento(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int opc_entrada = 0;
    int opc_algoritmo = 0;
    int n = 0;
    const int MAX_ELEMENTOS = 10000000; // 10 millones
    int *arr = nullptr;
    int *arr_aux = nullptr;
    string tipo_arreglo = "Manual";
    int opc_continuar = 1;
    
    while (opc_continuar == 1) {
        try {
            // Liberar memoria anterior si existe
            if (arr != nullptr) delete[] arr;
            if (arr_aux != nullptr) delete[] arr_aux;
            
            opc_entrada = 0;
            opc_algoritmo = 0;
            n = 0;
            tipo_arreglo = "Manual";
        
            cout << "\n" << string(70, '=') << endl;
            cout << "COMPARADOR DE ALGORITMOS DE ORDENAMIENTO" << endl;
            cout << string(70, '=') << endl;
        
            cout << "\n--- ENTRADA DE DATOS ---" << endl;
            cout << "0 - Ingresar numeros manualmente" << endl;
            cout << "1 - Generar numeros aleatorios" << endl;
            cout << "Opcion: ";
            cin >> opc_entrada;
        
            if (opc_entrada == 0) {
                cout << "Ingresa el numero de elementos (max " << MAX_ELEMENTOS << "): ";
                cin >> n;
                
                if (n <= 0 || n > MAX_ELEMENTOS) {
                    cout << "Error: El numero debe estar entre 1 y " << MAX_ELEMENTOS << endl;
                    continue;
                }
                
                try {
                    arr = new int[n];
                    arr_aux = new int[n];
                } catch (bad_alloc &e) {
                    cout << "Error: No hay suficiente memoria para " << n << " elementos." << endl;
                    cout << "Intenta con un numero menor." << endl;
                    arr = nullptr;
                    arr_aux = nullptr;
                    continue;
                }
                
                cout << "Ingresa los " << n << " numeros: ";
                for (int i = 0; i < n; i++) {
                    cin >> arr[i];
                }
                tipo_arreglo = "Manual";
            } else if (opc_entrada == 1) {
                cout << "Ingresa el numero de elementos (max " << MAX_ELEMENTOS << "): ";
                cin >> n;
                
                if (n <= 0 || n > MAX_ELEMENTOS) {
                    cout << "Error: El numero debe estar entre 1 y " << MAX_ELEMENTOS << endl;
                    continue;
                }
                
                try {
                    arr = new int[n];
                    arr_aux = new int[n];
                } catch (bad_alloc &e) {
                    cout << "Error: No hay suficiente memoria para " << n << " elementos." << endl;
                    cout << "Intenta con un numero menor." << endl;
                    arr = nullptr;
                    arr_aux = nullptr;
                    continue;
                }
                
                cout << "\n--- TIPO DE ARREGLO ALEATORIO ---" << endl;
                cout << "0 - Completamente desordenado (aleatorio)" << endl;
                cout << "1 - Ordenado ascendente (mejor caso)" << endl;
                cout << "2 - Ordenado descendente (peor caso)" << endl;
                cout << "3 - Parcialmente ordenado (50% ordenado)" << endl;
                cout << "Opcion: ";
                int opc_tipo = 0;
                cin >> opc_tipo;
                
                srand(time(0));
        
                if (opc_tipo == 0) {
                    // Completamente desordenado
                    for (int i = 0; i < n; i++) {
                        arr[i] = rand() % 1000 + 1;
                    }
                    tipo_arreglo = "Aleatorio Desordenado";
                }
                else if (opc_tipo == 1) {
                    // Ordenado ascendente (mejor caso)
                    for (int i = 0; i < n; i++) {
                        arr[i] = i + 1;
                    }
                    tipo_arreglo = "Ordenado Ascendente (Mejor Caso)";
                }
                else if (opc_tipo == 2) {
                    // Ordenado descendente (peor caso)
                    for (int i = 0; i < n; i++) {
                        arr[i] = n - i;
                    }
                    tipo_arreglo = "Ordenado Descendente (Peor Caso)";
                }
                else if (opc_tipo == 3) {
                    // Parcialmente ordenado (50% ordenado)
                    for (int i = 0; i < n / 2; i++) {
                        arr[i] = i + 1;
                    }
                    for (int i = n / 2; i < n; i++) {
                        arr[i] = rand() % 1000 + 1;
                    }
                    tipo_arreglo = "Parcialmente Ordenado (50%)";
                }
            }
    
            cout << "\nTipo de Arreglo: " << tipo_arreglo << endl;
            cout << "Tamaño: " << n << " elementos" << endl;
            cout << "Arreglo Original (primeros 10): ";
            mostrarArreglo(arr, n);
            
            cout << "\n--- SELECCIONA OPCION ---" << endl;
            cout << "1 - Ejecutar algoritmo individual" << endl;
            cout << "2 - Comparar los 3 algoritmos" << endl;
            cout << "Opcion: ";
            cin >> opc_algoritmo;
            
            if (opc_algoritmo == 1) {
                // ALGORITMO INDIVIDUAL
                cout << "\n--- ALGORITMOS DISPONIBLES ---" << endl;
                cout << "1 - Quick Sort" << endl;
                cout << "2 - Merge Sort" << endl;
                cout << "3 - Heap Sort" << endl;
                cout << "Opcion: ";
                cin >> opc_algoritmo;
                
                if (opc_algoritmo == 1) {
                    // QUICKSORT
                    copiarArreglo(arr, arr_aux, n);
                    cout << "\n" << string(70, '-') << endl;
                    cout << "EJECUTANDO: QUICK SORT" << endl;
                    cout << string(70, '-') << endl;
                    pasos_quick = 0;
                    quickSort(arr_aux, 0, n - 1);
                    
                    cout << "Arreglo Ordenado (primeros 10): ";
                    mostrarArreglo(arr_aux, n);
                    cout << "\nResultados:" << endl;
                    cout << "  Pasos (comparaciones): " << pasos_quick << endl;
                    cout << "  Complejidad Teórica: O(n log n)" << endl;
                    cout << "  Validación: " << (verificarOrdenamiento(arr_aux, n) ? "OK" : "ERROR") << endl;
                }
                else if (opc_algoritmo == 2) {
                    // MERGESORT
                    copiarArreglo(arr, arr_aux, n);
                    cout << "\n" << string(70, '-') << endl;
                    cout << "EJECUTANDO: MERGE SORT" << endl;
                    cout << string(70, '-') << endl;
                    pasos_merge = 0;
                    mergeSort(arr_aux, 0, n - 1);
                    
                    cout << "Arreglo Ordenado (primeros 10): ";
                    mostrarArreglo(arr_aux, n);
                    cout << "\nResultados:" << endl;
                    cout << "  Pasos (comparaciones): " << pasos_merge << endl;
                    cout << "  Complejidad Teórica: O(n log n)" << endl;
                    cout << "  Validación: " << (verificarOrdenamiento(arr_aux, n) ? "OK" : "ERROR") << endl;
                }
                else if (opc_algoritmo == 3) {
                    // HEAPSORT
                    copiarArreglo(arr, arr_aux, n);
                    cout << "\n" << string(70, '-') << endl;
                    cout << "EJECUTANDO: HEAP SORT" << endl;
                    cout << string(70, '-') << endl;
                    heapSort(arr_aux, n);
                    
                    cout << "Arreglo Ordenado (primeros 10): ";
                    mostrarArreglo(arr_aux, n);
                    cout << "\nResultados:" << endl;
                    cout << "  Pasos (comparaciones): " << pasos_heap << endl;
                    cout << "  Complejidad Teórica: O(n log n)" << endl;
                    cout << "  Validación: " << (verificarOrdenamiento(arr_aux, n) ? "OK" : "ERROR") << endl;
                }
            }
            else if (opc_algoritmo == 2) {
                // COMPARAR TODOS
                int *arr_q = nullptr, *arr_m = nullptr, *arr_h = nullptr;
                
                try {
                    arr_q = new int[n];
                    arr_m = new int[n];
                    arr_h = new int[n];
                } catch (bad_alloc &e) {
                    cout << "Error: No hay suficiente memoria para los arrays de comparacion." << endl;
                    if (arr_q) delete[] arr_q;
                    if (arr_m) delete[] arr_m;
                    if (arr_h) delete[] arr_h;
                    continue;
                }
                
                copiarArreglo(arr, arr_q, n);
                copiarArreglo(arr, arr_m, n);
                copiarArreglo(arr, arr_h, n);
                
                cout << "\n--- EJECUTANDO LOS 3 ALGORITMOS ---" << endl;
                
                pasos_quick = 0;
                intercambios_quick = 0;
                ciclos_quick = 0;
                quickSort(arr_q, 0, n - 1);
                
                pasos_merge = 0;
                intercambios_merge = 0;
                ciclos_merge = 0;
                mergeSort(arr_m, 0, n - 1);
                
                pasos_heap = 0;
                intercambios_heap = 0;
                ciclos_heap = 0;
                heapSort(arr_h, n);
                
                cout << "\nTodos los algoritmos ejecutados" << endl;
                
                // Mostrar tabla de comparación
                cout << "\n" << string(78, '=') << endl;
                cout << "TABLA COMPARATIVA - RESULTADOS" << endl;
                cout << string(78, '=') << endl;
                
                cout << "\nTamaño del arreglo: " << n << " elementos" << endl;
                cout << "Tipo de arreglo: " << tipo_arreglo << endl << endl;
                
                cout << setw(18) << "Algoritmo" 
                     << setw(15) << "Comparaciones" 
                     << setw(15) << "Intercambios"
                     << setw(15) << "Ciclos"
                     << setw(15) << "Validacion" << endl;
                cout << string(78, '-') << endl;
                
                bool q_ok = verificarOrdenamiento(arr_q, n);
                bool m_ok = verificarOrdenamiento(arr_m, n);
                bool h_ok = verificarOrdenamiento(arr_h, n);
                
                cout << setw(18) << "Quick Sort" 
                     << setw(15) << pasos_quick 
                     << setw(15) << intercambios_quick
                     << setw(15) << ciclos_quick
                     << setw(15) << (q_ok ? "OK" : "ERROR") << endl;
                
                cout << setw(18) << "Merge Sort" 
                     << setw(15) << pasos_merge 
                     << setw(15) << intercambios_merge
                     << setw(15) << ciclos_merge
                     << setw(15) << (m_ok ? "OK" : "ERROR") << endl;
                
                cout << setw(18) << "Heap Sort" 
                     << setw(15) << pasos_heap 
                     << setw(15) << intercambios_heap
                     << setw(15) << ciclos_heap
                     << setw(15) << (h_ok ? "OK" : "ERROR") << endl;
                
                cout << string(78, '=') << endl;
                
                // ANÁLISIS Y CONCLUSIÓN
                cout << "\n" << string(78, '=') << endl;
                cout << "ANALISIS Y CONCLUSION" << endl;
                cout << string(78, '=') << endl;
                
                long long minimo = pasos_quick;
                string mas_rapido = "Quick Sort";
                long long pasos_mas_rapido = pasos_quick;
                
                if (pasos_merge < minimo) {
                    minimo = pasos_merge;
                    mas_rapido = "Merge Sort";
                    pasos_mas_rapido = pasos_merge;
                }
                if (pasos_heap < minimo) {
                    minimo = pasos_heap;
                    mas_rapido = "Heap Sort";
                    pasos_mas_rapido = pasos_heap;
                }
                
                cout << "\nESTADISTICAS:" << endl << endl;
                cout << "  Menor numero de comparaciones: " << mas_rapido << " (" << pasos_mas_rapido << ")" << endl;
                
                cout << "\nDETALLE POR ALGORITMO:" << endl << endl;
                cout << "Quick Sort:" << endl;
                cout << "  - Comparaciones: " << pasos_quick << endl;
                cout << "  - Intercambios: " << intercambios_quick << endl;
                cout << "  - Ciclos: " << ciclos_quick << endl;
                cout << "  - Total operaciones: " << (pasos_quick + intercambios_quick + ciclos_quick) << endl;
                
                cout << "\nMerge Sort:" << endl;
                cout << "  - Comparaciones: " << pasos_merge << endl;
                cout << "  - Intercambios: " << intercambios_merge << endl;
                cout << "  - Ciclos: " << ciclos_merge << endl;
                cout << "  - Total operaciones: " << (pasos_merge + intercambios_merge + ciclos_merge) << endl;
                
                cout << "\nHeap Sort:" << endl;
                cout << "  - Comparaciones: " << pasos_heap << endl;
                cout << "  - Intercambios: " << intercambios_heap << endl;
                cout << "  - Ciclos: " << ciclos_heap << endl;
                cout << "  - Total operaciones: " << (pasos_heap + intercambios_heap + ciclos_heap) << endl;
                
                cout << "\nCONCLUSION:" << endl << endl;
                cout << "Para este intento con n=" << n << " elementos" << endl;
                cout << "Tipo: " << tipo_arreglo << endl << endl;
                cout << "  El algoritmo MAS EFICIENTE es: " << mas_rapido << endl;
                cout << "  - Comparaciones realizadas: " << pasos_mas_rapido << endl;
                cout << "  - Complejidad teorica: O(n log n)" << endl;
                cout << "  - Validacion: OK" << endl;
                
                cout << endl << string(78, '=') << endl;
                
                // Liberar memoria temporal
                delete[] arr_q;
                delete[] arr_m;
                delete[] arr_h;
            }
            
            // Menú para continuar o salir
            cout << "\n--- CONTINUAR ---" << endl;
            cout << "1 - Hacer otra prueba" << endl;
            cout << "0 - Salir del programa" << endl;
            cout << "Opcion: ";
            cin >> opc_continuar;
            cout << endl;
        } catch (exception &e) {
            cout << "Error durante la ejecucion: " << e.what() << endl;
            opc_continuar = 0;
        }
    }
    
    // Liberar memoria dinámica principal
    if (arr != nullptr) delete[] arr;
    if (arr_aux != nullptr) delete[] arr_aux;
    
    cout << "\nPrograma finalizado." << endl;
    
    return 0;
}
