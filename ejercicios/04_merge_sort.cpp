#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int pasoActual = 1;
int nivelMaximo = 0;

void imprimirArreglo(const vector<int>& arr, int inicio = -1, int fin = -1, 
                      int i = -1, int j = -1, int k = -1) {
    cout << "  [ ";
    for (int idx = 0; idx < arr.size(); idx++) {
        bool esI = (i != -1 && idx == i);
        bool esJ = (j != -1 && idx == j);
        bool esK = (k != -1 && idx == k);
        
        if ((esI || esJ || esK) && (inicio == -1 || (idx >= inicio && idx <= fin))) {
            if (esI && esJ && esK) {
                cout << "\033[1;37m" << arr[idx] << "(i,j,k)\033[0m";
            } else if (esI && esJ) {
                cout << "\033[1;36m" << arr[idx] << "(i,j)\033[0m";
            } else if (esI && esK) {
                cout << "\033[1;33m" << arr[idx] << "(i,k)\033[0m";
            } else if (esJ && esK) {
                cout << "\033[1;34m" << arr[idx] << "(j,k)\033[0m";
            } else if (esI) {
                cout << "\033[1;32m" << arr[idx] << "(i)\033[0m";
            } else if (esJ) {
                cout << "\033[1;31m" << arr[idx] << "(j)\033[0m";
            } else if (esK) {
                cout << "\033[1;35m" << arr[idx] << "(k)\033[0m";
            }
        } else if (inicio != -1 && fin != -1 && idx >= inicio && idx <= fin) {
            cout << arr[idx];
        } else if (inicio == -1) {
            cout << arr[idx];
        } else {
            cout << "\033[90m" << arr[idx] << "\033[0m";
        }
        if (idx < arr.size() - 1) cout << ", ";
    }
    cout << " ]\n";
}

void merge(vector<int>& arr, int inicio, int medio, int fin, int nivel) {
    string indent(nivel * 2, ' ');
    
    cout << indent << "\n>>> FUSIONANDO subarreglos\n";
    cout << indent << "    Izquierdo: [" << inicio << ".." << medio << "] = [ ";
    for (int x = inicio; x <= medio; x++) {
        cout << arr[x];
        if (x < medio) cout << ", ";
    }
    cout << " ]\n";
    cout << indent << "    Derecho:   [" << (medio + 1) << ".." << fin << "] = [ ";
    for (int x = medio + 1; x <= fin; x++) {
        cout << arr[x];
        if (x < fin) cout << ", ";
    }
    cout << " ]\n\n";
    
    vector<int> izq(arr.begin() + inicio, arr.begin() + medio + 1);
    vector<int> der(arr.begin() + medio + 1, arr.begin() + fin + 1);
    
    int i = 0, j = 0, k = inicio;
    
    while (i < izq.size() && j < der.size()) {
        cout << indent << "  PASO " << pasoActual++ << ": Comparar izq[" << i << "]=" << izq[i] 
             << " con der[" << j << "]=" << der[j];
        
        if (izq[i] <= der[j]) {
            cout << " -> " << izq[i] << " <= " << der[j] << " (VERDADERO)\n";
            cout << indent << "     Copiar " << izq[i] << " a posicion " << k << "\n";
            arr[k++] = izq[i++];
        } else {
            cout << " -> " << izq[i] << " > " << der[j] << " (FALSO)\n";
            cout << indent << "     Copiar " << der[j] << " a posicion " << k << "\n";
            arr[k++] = der[j++];
        }
        cout << indent << "     Arreglo actual: ";
        imprimirArreglo(arr, inicio, fin);
        cout << "\n";
    }
    
    while (i < izq.size()) {
        cout << indent << "  PASO " << pasoActual++ << ": Copiar elemento restante izq[" << i 
             << "]=" << izq[i] << " a posicion " << k << "\n";
        arr[k++] = izq[i++];
        cout << indent << "     Arreglo actual: ";
        imprimirArreglo(arr, inicio, fin);
        cout << "\n";
    }
    
    while (j < der.size()) {
        cout << indent << "  PASO " << pasoActual++ << ": Copiar elemento restante der[" << j 
             << "]=" << der[j] << " a posicion " << k << "\n";
        arr[k++] = der[j++];
        cout << indent << "     Arreglo actual: ";
        imprimirArreglo(arr, inicio, fin);
        cout << "\n";
    }
    
    cout << indent << "\n>>> FUSION COMPLETADA\n";
    cout << indent << "    Resultado: [ ";
    for (int x = inicio; x <= fin; x++) {
        cout << arr[x];
        if (x < fin) cout << ", ";
    }
    cout << " ]\n";
}

void mergeSort(vector<int>& arr, int inicio, int fin, int nivel) {
    string indent(nivel * 2, ' ');
    nivelMaximo = max(nivelMaximo, nivel);
    
    if (inicio < fin) {
        cout << indent << "\n=== NIVEL " << nivel << " ===\n";
        cout << indent << "DIVIDIR: [" << inicio << ".." << fin << "] en dos mitades\n";
        cout << indent << "Arreglo actual: ";
        imprimirArreglo(arr, inicio, fin);
        
        int medio = inicio + (fin - inicio) / 2;
        
        cout << indent << "\nMitad izquierda: [" << inicio << ".." << medio << "]\n";
        mergeSort(arr, inicio, medio, nivel + 1);
        
        cout << indent << "\nMitad derecha: [" << (medio + 1) << ".." << fin << "]\n";
        mergeSort(arr, medio + 1, fin, nivel + 1);
        
        merge(arr, inicio, medio, fin, nivel);
    } else {
        cout << indent << "\n=== NIVEL " << nivel << " (BASE CASE) ===\n";
        cout << indent << "Elemento unico en posicion " << inicio << ": " << arr[inicio] << "\n";
        cout << indent << "No hay nada que dividir o fusionar\n";
    }
}

int main() {
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║    ALGORITMO MERGE SORT - PASO A PASO       ║\n";
    cout << "║                                            ║\n";
    cout << "║  (i) = Indice izquierdo                   ║\n";
    cout << "║  (j) = Indice derecho                     ║\n";
    cout << "║  (k) = Indice resultado                   ║\n";
    cout << "║                                            ║\n";
    cout << "║  FASE 1: DIVIDIR (Divide)                 ║\n";
    cout << "║  FASE 2: FUSIONAR (Conquer)               ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    
    cout << "\nArreglo Original: ";
    imprimirArreglo(arr);
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "INICIO DEL ALGORITMO MERGE SORT\n";
    cout << string(60, '=') << "\n";
    
    mergeSort(arr, 0, arr.size() - 1, 0);
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "ARREGLO FINAL ORDENADO: ";
    imprimirArreglo(arr);
    cout << string(60, '=') << "\n\n";
    
    return 0;
}
