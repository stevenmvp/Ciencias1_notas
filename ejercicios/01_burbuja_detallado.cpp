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

void burbuja(vector<int>& arr) {
    int n = arr.size();
    
    cout << "\nArreglo Original: ";
    imprimirArreglo(arr);
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "INICIO DEL ALGORITMO BURBUJA\n";
    cout << string(60, '=') << "\n";
    
    for (int i = 0; i < n - 1; i++) {
        cout << "\n>>> ITERACION EXTERNA i = " << i << "\n";
        cout << "    (Ultimo elemento ordenado en posicion " << (n - 1 - i) << ")\n";
        bool huboIntercambio = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            cout << "\n  PASO " << pasoActual++ << ": Comparar arr[" << j << "]=" << arr[j] 
                 << " con arr[" << (j + 1) << "]=" << arr[j + 1];
            
            if (arr[j] > arr[j + 1]) {
                cout << " -> " << arr[j] << " > " << arr[j + 1] << " (VERDADERO)\n";
                cout << "     INTERCAMBIAR posiciones " << j << " y " << (j + 1) << "\n";
                swap(arr[j], arr[j + 1]);
                huboIntercambio = true;
                cout << "     Arreglo actual: ";
                imprimirArreglo(arr, 0, n - i - 1, j, j + 1);
            } else {
                cout << " -> " << arr[j] << " <= " << arr[j + 1] << " (FALSO, no hay cambio)\n";
                cout << "     Arreglo actual: ";
                imprimirArreglo(arr, 0, n - i - 1, j, j + 1);
            }
        }
        
        cout << "\n  FIN ITERACION " << i << ": Arreglo actual: ";
        imprimirArreglo(arr);
        
        if (!huboIntercambio) {
            cout << "\n  >> NO HUBO INTERCAMBIOS EN ESTA ITERACION\n";
            cout << "  >> EL ARREGLO YA ESTA ORDENADO\n";
            break;
        }
    }
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "ARREGLO FINAL ORDENADO: ";
    imprimirArreglo(arr);
    cout << string(60, '=') << "\n\n";
}

int main() {
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║    ALGORITMO BURBUJA - PASO A PASO          ║\n";
    cout << "║                                            ║\n";
    cout << "║  (i) = Indice iteracion externa           ║\n";
    cout << "║  (j) = Indice iteracion interna           ║\n";
    cout << "║  (i,j) = Ambos indices                    ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    
    vector<int> arr = {38, 27, 43, 3, 9};
    
    burbuja(arr);
    
    return 0;
}
