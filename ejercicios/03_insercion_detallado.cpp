#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int pasoActual = 1;

void imprimirArreglo(const vector<int>& arr, int inicio = -1, int fin = -1, int i = -1, int j = -1) {
    cout << "  [ ";
    for (int idx = 0; idx < arr.size(); idx++) {
        if (idx == i && idx == j) {
            cout << "\033[1;36m" << arr[idx] << "(i,j)\033[0m"; // Cyan para ambos
        } else if (idx == i) {
            cout << "\033[1;35m" << arr[idx] << "(i)\033[0m"; // Magenta para i (elemento a insertar)
        } else if (idx == j) {
            cout << "\033[1;31m" << arr[idx] << "(j)\033[0m"; // Rojo para j
        } else if (inicio != -1 && fin != -1 && idx <= fin) {
            if (idx < inicio) {
                cout << "\033[1;32m" << arr[idx] << "\033[0m"; // Verde para partes ordenadas
            } else {
                cout << arr[idx];
            }
        } else if (inicio == -1) {
            cout << arr[idx];
        } else {
            cout << "\033[90m" << arr[idx] << "\033[0m"; // Gris para fuera de rango
        }
        if (idx < arr.size() - 1) cout << ", ";
    }
    cout << " ]\n";
}

void insercion(vector<int>& arr) {
    int n = arr.size();
    
    cout << "\nArreglo Original: ";
    imprimirArreglo(arr);
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "INICIO DEL ALGORITMO INSERCION\n";
    cout << string(60, '=') << "\n";
    
    for (int i = 1; i < n; i++) {
        cout << "\n>>> ITERACION " << i << ": Insertar elemento en posicion " << i << "\n";
        int clave = arr[i];
        cout << "    CLAVE A INSERTAR: " << clave << "\n";
        cout << "    PARTE ORDENADA: [ ";
        for (int k = 0; k < i; k++) {
            cout << arr[k];
            if (k < i - 1) cout << ", ";
        }
        cout << " ]\n\n";
        
        int j = i - 1;
        
        while (j >= 0) {
            cout << "  PASO " << pasoActual++ << ": Comparar clave=" << clave 
                 << " con arr[" << j << "]=" << arr[j];
            
            if (arr[j] > clave) {
                cout << " -> " << arr[j] << " > " << clave << " (VERDADERO)\n";
                cout << "     DESPLAZAR arr[" << j << "]=" << arr[j] 
                     << " a posicion " << (j + 1) << "\n";
                arr[j + 1] = arr[j];
                cout << "     Arreglo actual: ";
                imprimirArreglo(arr, 0, i, i, j);
                j--;
            } else {
                cout << " -> " << arr[j] << " <= " << clave << " (FALSO)\n";
                cout << "     POSICION CORRECTA ENCONTRADA EN INDICE " << (j + 1) << "\n";
                cout << "     Arreglo actual: ";
                imprimirArreglo(arr, 0, i, i, j);
                break;
            }
            cout << "\n";
        }
        
        cout << "  PASO " << pasoActual++ << ": Insertar clave=" << clave 
             << " en posicion " << (j + 1) << "\n";
        arr[j + 1] = clave;
        cout << "     Arreglo actualizado: ";
        imprimirArreglo(arr, 0, i);
        cout << "     Parte ordenada: [ ";
        for (int k = 0; k <= i; k++) {
            cout << arr[k];
            if (k < i) cout << ", ";
        }
        cout << " ]\n";
    }
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "ARREGLO FINAL ORDENADO: ";
    imprimirArreglo(arr);
    cout << string(60, '=') << "\n\n";
}

int main() {
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║   ALGORITMO INSERCION - PASO A PASO         ║\n";
    cout << "║                                            ║\n";
    cout << "║  (i) = Elemento a insertar                ║\n";
    cout << "║  (j) = Indice comparando                  ║\n";
    cout << "║  Verde = Parte ya ordenada                ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    
    vector<int> arr = {38, 27, 43, 3, 9};
    
    insercion(arr);
    
    return 0;
}
